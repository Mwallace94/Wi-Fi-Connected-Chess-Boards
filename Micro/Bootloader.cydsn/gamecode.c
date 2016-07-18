
#include "gamecode.h"
#include <strings.h>

// Common messages to send to server
//.connect
char bstr_connect[8] = { 0x2E, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74 };
//.ready
char bstr_ready[6] = {0x2E, 0x72, 0x65, 0x61, 0x64, 0x79};
//.gib
char bstr_gib[4] = {0x2E, 0x67, 0x69, 0x62};

// Can receive response from server of sizes 1, 8, or 9.
char bres1[1];
char bres8[8];
char bres9[9];

int diff_loc[2][2];
// Different board states to use at this time.
char initial_board[8][12];
char update1_board[8][12];
char update2_board[8][12];

enum Diff {
    UPDATE1 = 1,
    UPDATE2 = 2,
};

// Initialization functions.

/*
	Initalizes the game state and board state.
*/
int initialize() {

	int new_game_state;

	new_game_state = CONNECTED;
	return new_game_state;
}

// State functions.

/*
	Runs when game_state == NOTCONNECTED
*/
int state_notconnected() {

	Debug_UART_PutString("NOTCONNECTED\n");

	// write ".connect"
	strcpy(bres1, "");
		esp_transmit(bstr_connect, "8");
        strncpy(bres1, recv, 1);
        Debug_UART_PutChar(recv[0] + 48);
        Debug_UART_PutString("<-here\n");
	

	if(bres1[0] == 0x01 || bres1[0] == 0x03) {

		Debug_UART_PutString("Connected.\n");
		game_state = CONNECTED;
	}
	else {

		Debug_UART_PutString("Not connected.\n");
		game_state = NOTCONNECTED;
	}
	return game_state;
}

/*
	Runs when game_state == CONNECTED
*/
int state_connected() {

	Debug_UART_PutString("CONNECTED\n");

	// write ".ready"
	strcpy(bres1, "");
	esp_transmit(bstr_ready, "6");
    strncpy(bres1, recv, 1);
    Debug_UART_PutChar(recv[0] + 48);
    Debug_UART_PutString("<-here\n");

	if(bres1[0] == 0x11){
		Debug_UART_PutString("Ready.");
		game_state = READY;
	}

	else if(bres1[0] == 0x21 || bres1[0] == '!') {

		Debug_UART_PutString("Your turn.");
		game_state = MOVING;
	}
	else if(bres1[0] == 0x22 || bres1[0] == '"') {

		Debug_UART_PutString("Their turn.");
		game_state = WAITING;
	}
	else {
		Debug_UART_PutString("Connection State Failure.");
		game_state = CONNECTED;
	}

	return game_state;
}

/*
	Runs when game_state == READY
*/
int state_ready() {

	Debug_UART_PutString("READY\n");

	//write ".gib"
	strcpy(bres1, "");
	esp_transmit(bstr_gib, "4");
    strncpy(bres1, recv, 1);
    
	while(	bres1[0] != 0x21 && bres1[0] != 0x22 && 
			bres1[0] != '!'  && bres1[0] != '"') { 
		CyDelay(5000);

		esp_transmit(bstr_gib, "4");
        strncpy(bres1, recv, 1);

		Debug_UART_PutString(&bres1[0]);
	}

	if(bres1[0] == 0x11) {
		game_state = READY;
	} 
	else if(bres1[0] == 0x21 || bres1[0] == '!') {

		Debug_UART_PutString("Your turn.");
		game_state = MOVING;
	} 
	else if(bres1[0] == 0x22 || bres1[0] == '"') {

		Debug_UART_PutString("Their turn.");
		game_state = WAITING;
	}
	return game_state;
}

/*
	Runs when game_state == WAITING
*/
int state_waiting() {

	Debug_UART_PutString("WAITING");

	// write ".gib"
	strcpy(bres8, "");
    //esp_transmit(bstr_gib, "4");
    //strncpy(bres8, recv, 8);
    
	while(bres8[1] == 0x00) {
		CyDelay(5000);

		esp_transmit(bstr_gib, "4");
        strncpy(bres8, recv, 8);
        
		Debug_UART_PutString(bres8);

		if(bres8[0] == 0x31 || bres8[0] == '1'){
			game_state = CONNECTED;
			break;
		}
	}
	if(bres8[0] == 0x31 || bres8[0] == '1'){
		game_state = CONNECTED;
		return game_state;
	}
	char movementOpp1[4] = { bres8[1], bres8[0], bres8[3], bres8[2] };
	char movementOpp2[4] = { bres8[5], bres8[4], bres8[7], bres8[6] };

	if(	movementOpp2[0] != 0 && movementOpp2[1] != 0 && 
		movementOpp2[2] != 0 && movementOpp2[3] != 0) {
		Debug_UART_PutString(movementOpp2);
        move.fromCol = (int) movementOpp2[0];
        move.fromRow = (int) movementOpp2[1];
        move.toCol = (int) movementOpp2[2];
        move.toRow = (int) movementOpp2[3];
		movepiece(move);
	}
	Debug_UART_PutString(movementOpp1);
    move.fromCol = (int) movementOpp1[0];
    move.fromRow = (int) movementOpp1[1];
    move.toCol = (int) movementOpp1[2];
    move.toRow = (int) movementOpp1[3];
	movepiece(move);

	game_state = MOVING;
	return game_state;
}

void diff_boards(enum Diff x) {

	diff_loc[0][0] = 0;
    diff_loc[0][1] = 0;
    diff_loc[1][0] = 0;
    diff_loc[1][1] = 0;

	int i, j;
    if(x == UPDATE1) {
        for(i = 0; i < 8; i++) {
    		for(j = 0; j < 12; j++) {

    			// Pick-up location, use diff_loc[0].
    			if(initial_board[i][j] == 0x01 && update1_board[i][j] == 0x00) {

    				// Picked up in graveyard, warn user.
    				if((j % 10) == 0 || (j % 10) == 1) {
    					Debug_UART_PutString("Do not pick up graveyard pieces!\n");
    				}
    				else {
    					diff_loc[0][0] = i;
    					diff_loc[0][1] = j;
    				}
    			}
    			// Drop-off location, use diff_loc[1].
    			else if(initial_board[i][j] == 0x00 && update1_board[i][j] == 0x01) {

    				diff_loc[1][0] = i;
    				diff_loc[1][1] = j;
    			}
    		}
    	}    
    }
    else {
        for(i = 0; i < 8; i++) {
    		for(j = 0; j < 12; j++) {

    			// Pick-up location, use diff_loc[0].
    			if(update1_board[i][j] == 0x01 && update2_board[i][j] == 0x00) {

    				// Picked up in graveyard, warn user.
    				if((j % 10) == 0 || (j % 10) == 1) {
    					Debug_UART_PutString("Do not pick up graveyard pieces!\n");
    				}
    				else {
    					diff_loc[0][0] = i;
    					diff_loc[0][1] = j;
    				}
    			}
    			// Drop-off location, use diff_loc[1].
    			else if(update1_board[i][j] == 0x00 && update2_board[i][j] == 0x01) {

    				diff_loc[1][0] = i;
    				diff_loc[1][1] = j;
    			}
    		}
    	}
    }
}

uint8 itoc(int i) {
	switch(i) {
		case 0: return 0x30;
		case 1: return 0x31;
		case 2: return 0x32;
		case 3: return 0x33;
		case 4: return 0x34;
		case 5: return 0x35;
		case 6: return 0x36;
		case 7: return 0x37;
		case 8: return 0x38;
		case 9: return 0x39;
		case 10: return 0x41;
		case 11: return 0x42;
		case 12: return 0x43;
		case 13: return 0x44;
		case 14: return 0x45;
		default: return 0x46;
	}
}

/*
	Runs when game_state == MOVING
	Helpers: diff_boards(bold, bnew)
*/
int state_moving() {

	Debug_UART_PutString("MOVING");

	// initial_board holds the state of the board just before this call.
	read_reed_switches();
	memcpy(&initial_board, &board, sizeof(board));

	// Locations of piece movement.
	int move1[2][2] = { { 0, 0 }, { 0, 0 } };
	int move2[2][2] = { { 0, 0 }, { 0, 0 } };
	char locs[4] = { 0x00, 0x00, 0x00, 0x00 };

	// Flag for castling.
	int castling = 0;

	while(  move1[0][0] == 0 && 
            move1[0][1] == 0 &&
            move1[1][0] == 0 &&
            move1[1][1] == 0) {

		CyDelay(1000);
		read_reed_switches();
		memcpy(&update1_board, &board, sizeof(board));

		diff_boards(UPDATE1);

        move1[0][0] = diff_loc[0][0];
        move1[0][1] = diff_loc[0][1];
        move1[1][0] = diff_loc[1][0];
        move1[1][1] = diff_loc[1][1];
        
		if( ((move1[0][0] == 0 && move1[0][1] == 6) || 
            (move1[0][0] == 7 && move1[0][1] == 6 )) &&
			((move1[1][1] - move1[0][1]) == -2 || 
			(move1[1][1] - move1[0][1]) == 2)) {

			castling = 1;
		}
	}
	locs[0] = itoc(move1[0][1]); 
	locs[1]	= itoc(move1[0][0]); 
	locs[2]	= itoc(move1[1][1]); 
	locs[3]	= itoc(move1[1][0]);

	// Moved piece to graveyard, get corresponding attack OR castling.
	if((move1[1][1] % 10) == 0 || (move1[1][1] % 10) == 1 || castling) {

		while(  move2[0][0] == 0 && 
                move2[0][1] == 0 &&
                move2[1][0] == 0 &&
                move2[1][1] == 0) {

			CyDelay(1000);
			read_reed_switches();
			memcpy(&update2_board, &board, sizeof(board));

            diff_boards(UPDATE2);

            move2[0][0] = diff_loc[0][0];
            move2[0][1] = diff_loc[0][1];
            move2[1][0] = diff_loc[1][0];
            move2[1][1] = diff_loc[1][1];
        
			if(!castling) {
	            locs[0] = itoc(move2[0][1]); 
	            locs[1]	= itoc(move2[0][0]); 
	            locs[2]	= itoc(move2[1][1]); 
	            locs[3]	= itoc(move2[1][0]);
			}
		}
	}
	// Construct message to send to server.
	// ".move (space) fromCol (s) fromRow (s) toCol (s) toRow"
	char msg[13] = {0x2E, 0x6D, 0x6F, 0x76, 0x65, 0x20, 
			        locs[0], 0x20, locs[1], 0x20, locs[2], 0x20, locs[3] };

	strcpy(bres9, "");
	while(!strcmp(bres9, "")) {
		esp_transmit(msg, "13");
	    strncpy(bres9, recv, 9);
    }

	if(bres9[0] != 0x01) {
		Debug_UART_PutString("Invalid move, please undo changes.\n");
		game_state = MOVING;
	}
	else {
		Debug_UART_PutString("Valid move.\n");
		game_state = WAITING;
	}
	return game_state;
}

int game() {

	game_state = NOTCONNECTED;
    
    move_home();

	game_state = state_notconnected();

	while(1) {

		if(game_state == NOTCONNECTED) { 
			Debug_UART_PutString("Attempting to connect again.\n");
			state_notconnected(); 
		}

		else if(game_state == CONNECTED) {
		 	state_connected();
		}

		else if(game_state == READY) {
		 	state_ready();
		}

		else if(game_state == WAITING) { 
			state_waiting(); 
		}

		else if(game_state == MOVING) {
			state_moving(); 
		}

	}

}
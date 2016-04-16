
#include "gamecode.h"

// Can receive response from server of sizes 1, 8, or 9.
char bres1[1];
char bres8[8];
char bres9[9];


// Initialization functions.

/*
	Creates a socket file desc 
*/
int setup_connection() {

	int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    inet_pton(AF_INET, SERVER, &(servaddr.sin_addr));
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    return sockfd;
}

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
	int sockfd = setup_connection();

	// write ".connect"
	write(sockfd, &bstr_connect, 8);
	read(sockfd, &bres1, 1);

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
	int sockfd = setup_connection();

	// write ".ready"
	write(sockfd, &bstr_ready, 6);
	read(sockfd, &bres1, 1);

	if(bres1[0] == 0x11){
		Debug_UART_PutString("Ready.");
		game_state = READY;
	}

	if(bres[0] == 0x21 || bres[0] == '!') {

		Debug_UART_PutString("Your turn.");
		game_state = MOVING;
	}
	else if(bres[0] == 0x22 || bres[0] == '"') {

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
	int sockfd = setup_connection();

	//write ".gib"
	write(sockfd, &bstr_gib, 4);
	read(sockfd, &bres1, 1);

	while(	bres1[0] != 0x21 && bres1[0] != 0x22 && 
			bres1[0] != '!'  && bres1[0] != '"') { 
		sleep(5);
		sockfd = setup_connection();

		write(sockfd, &bstr_gib, 4);
		read(sockfd, &bres1, 1);

		Debug_UART_PutString(bres1[0]);
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
	int sockfd = setup_connection();

	// write ".gib"
	write(sockfd, &bstr_gib, 4);
	read(sockfd, &bres8, 8);

	while(strlen(bres8) != 8) {
		sleep(5);
		sockfd = setup_connection();

		write(sockfd, &bstr_gib, 4);
		read(sockfd, &bres8, 8);

		Debug_UART_PutString(bres8);

		if(bres8[0] == 0x31 || bres8[0] = '1'){
			game_state = CONNECTED;
			break;
		}
	}
	if(bres8[0] == 0x31 || bres8[0] = '1'){
		game_state = CONNECTED;
		return game_state;
	}
	char movementOpp1[4] = { bres8[1], bres8[0], bres8[3], bres8[2] };
	char movementOpp1Piece = { board[bres8[1]][bres8[0]] };

	char movementOpp2[5] = { bres8[5], bres8[4], bres8[7], bres8[6] };
	char movementOpp2Piece = { board[bres8[5]][bres8[4]] };

	if(	movementOpp2[0] != 0 && movementOpp2[1] != 0 && 
		movementOpp2[2] != 0 && movementOpp2[3] != 0) {
		Debug_UART_PutString(movementOpp2);
		//movepiece(board,movementOpp2);
	}
	Debug_UART_PutString(movementOpp1);
	//movepiece(board,movementOpp1);

	/*
	memset(&movementOpp1[0],'0',sizeof(movementOpp1));
	memset(&movementOpp1Piece[0],'0',sizeof(movementOpp1Piece));
	memset(&movementOpp2[0],'0',sizeof(movementOpp2));
	memset(&movementOpp2Piece[0],'0',sizeof(movementOpp2Piece));
	*/
	game_state = MOVING;
	return game_state;
}

int** diff_boards(char** bold, char** bnew) {

	int diff_loc[2][2] = { { 0, 0 }, { 0, 0 } };

	int i, j;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 12; j++) {

			// Pick-up location, use diff_loc[0].
			if(bold[i][j] == 0x01 && bnew[i][j] == 0x00) {

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
			else if(bold[i][j] == 0x00 && bnew[i][j] == 0x01) {

				diff_loc[1][0] = i;
				diff_loc[1][1] = j;
			}
		}
	}
	return diff_loc;
}

char itoc(int i) {
	switch(i) {
		case 0: return 0x00;
		case 1: return 0x01;
		case 2: return 0x02;
		case 3: return 0x03;
		case 4: return 0x04;
		case 5: return 0x05;
		case 6: return 0x06;
		case 7: return 0x07;
		case 8: return 0x08;
		case 9: return 0x09;
		case 10: return 0x0A;
		case 11: return 0x0B;
		case 12: return 0x0C;
		case 13: return 0x0D;
		case 14: return 0x0E;
		default: return 0x0F;
	}
}

/*
	Runs when game_state == MOVING
	Helpers: diff_boards(bold, bnew)
*/
int state_moving() {

	Debug_UART_PutString("MOVING");

	// Different board states to use at this time.
	char initial_board[8][12];
	char update1_board[8][12];
	char update2_board[8][12];

	// initial_board holds the state of the board just before this call.
	read_reed_switches();
	memcpy(&initial_board, &board, sizeof(board));

	// Locations of piece movement.
	int move1[2][2] = { { 0, 0 }, { 0, 0 } };
	int move2[2][2] = { { 0, 0 }, { 0, 0 } };
	char locs[4] = { 0x00, 0x00, 0x00, 0x00 };

	// Flag for castling.
	int castling = 0;

	while(move1 == { { 0, 0 }, { 0, 0 } }) {

		//sleep(1);
		read_reed_switches();
		memcpy(&update1_board, &board, sizeof(board));

		move1 = diff_boards(initial_board, update1_board);

		if(	(move1[0] == { 0, 6 } || 
			move1[0] == { 7, 6 }) &&
			((move1[1][1] - move1[0][1]) == -2 || 
			(move1[1][1] - move1[0][1]) == 2)) {

			castling = 1;
		}
	}
	locs[4] = { itoc(move1[0][1]), 
				itoc(move1[0][0]), 
				itoc(move1[1][1]), 
				itoc(move1[1][0]) };

	// Moved piece to graveyard, get corresponding attack OR castling.
	if((move1[1][1] % 10) == 0 || (move1[1][1] % 10) == 1 || castling) {

		while(move2 == { { 0, 0 }, { 0, 0 } }) {

			//sleep(1);
			read_reed_switches();
			memcpy(&update2_board, &board, sizeof(board));

			move2 = diff_boards(update1_board, update2_board);
			if(!castling) {
				locs[4] = { itoc(move2[0][1]), 
							itoc(move2[0][0]), 
							itoc(move2[1][1]), 
							itoc(move2[1][0]) };
			}
		}
	}
	// Construct message to send to server.
	// ".move (space) fromCol (s) fromRow (s) toCol (s) toRow"
	char msg[13];
	msg = { 0x2E, 0x6D, 0x6F, 0x76, 0x65, 0x20, 
			locs[0], 0x20, locs[1], 0x20, locs[2], 0x20, locs[3] };

	int sockfd = setup_connection();

	write(sockfd, &msg, 13);
	read(sockfd, &bres9, 9); // We don't need all 9 bytes.

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

int main(int argc, char** argv) {

	game_state = NOTCONNECTED;

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



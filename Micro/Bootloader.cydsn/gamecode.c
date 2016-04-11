
#include "gamecode.h"

// Initialization functions.

/*
	Creates a socket file desc 
*/
int setup_connection() {

	return 0;
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
	Runs when game_state == CONNECTED
*/
int state_connected() {

	int new_game_state;

	new_game_state = READY;
	return new_game_state;
}

/*
	Runs when game_state == READY
*/
int state_ready() {

	int new_game_state;

	new_game_state = WAITING; // or MOVING
	return new_game_state;
}

/*
	Runs when game_state == WAITING
*/
int state_waiting() {

	int new_game_state;

	new_game_state = MOVING;
	return new_game_state;
}

/*
	Runs when game_state == MOVING
*/
int state_moving() {

	int new_game_state;

	new_game_state = WAITING;
	return new_game_state;
}




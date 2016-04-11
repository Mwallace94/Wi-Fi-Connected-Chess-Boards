#ifndef GAMECODE_H
#define GAMECODE_H

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

// States of game (a la state machine)

int game_state;

#define NOTCONNECTED = 0
#define CONNECTED    = 1
#define READY        = 2
#define WAITING      = 3
#define MOVING       = 4

// Functions for initialization (and helpers)

int setup_connection();

int initialize();

// Functions for game states (and helper functions for each)
// These will be run inside individual while loops in main()
// Each of these returns an updated game_state.

int state_connected();

int state_ready();

int state_waiting();

int state_moving();





#endif
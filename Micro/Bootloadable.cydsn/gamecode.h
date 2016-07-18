#ifndef GAMECODE_H
#define GAMECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "board.h"
#include "espwifi.h"
    
// Server and port

#define SERVER "192.168.173.1"
#define PORT   666

//initialization of movement struct
struct movement move;        

// States of game (a la state machine)

#define NOTCONNECTED   0
#define CONNECTED      1
#define READY          2
#define WAITING        3
#define MOVING         4
    
enum Wait {
    NATURAL = 1,
    ARTIFICIAL = 2
};

int game_state;

// Functions for initialization (and helpers)

int setup_connection();

int initialize();

// Functions for game states (and helper functions for each)
// These will be run inside individual while loops in main()
// Each of these returns an updated game_state.

int state_notconnected();

int state_connected();

int state_ready();

int state_waiting(enum Wait x);

int state_moving();

int game();

extern char recv[9];



#endif

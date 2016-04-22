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
    
// Common messages to send to server

//.connect
char bstr_connect[8] = { 0x2E, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74 };

//.ready
char bstr_ready[6] = {0x2E, 0x72, 0x65, 0x61, 0x64, 0x79};

//.gib
char bstr_gib[4] = {0x2E, 0x67, 0x69, 0x62};


// States of game (a la state machine)

#define NOTCONNECTED   0
#define CONNECTED      1
#define READY          2
#define WAITING        3
#define MOVING         4

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

int state_waiting();

int state_moving();







#endif
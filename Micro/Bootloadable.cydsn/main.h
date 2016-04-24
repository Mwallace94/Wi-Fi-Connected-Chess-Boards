#ifndef MAIN_H
#define MAIN_H
    
#include <stdlib.h>
#include <project.h>
#include "board.h"
#include "espwifi.h"
#include "gamecode.h"
    
void init();

void debug();

extern char board[8][12];

struct movement move;
    
#endif  

#ifndef BOARD_H
#define BOARD_H

#include<project.h>

// Motor Constants
    
#define STEPS_PER_MM 10
    
#define MIN_X_POS 0
#define MAX_X_POS 10000
#define MIN_Y_POS 0
#define MAX_Y_POS 10000
    
// Motor Variables
    
int16 x_pos;
int16 y_pos;
    
// Motor Functions

void move_home();
void move_x(int16 mm);
void move_y(int16 mm);
void limitTest();

// Reed Switch Variables

char board[8][12];

// Reed Switch Functions

void read_reed_switches();

#endif 
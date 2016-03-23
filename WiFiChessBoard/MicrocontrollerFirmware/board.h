#ifndef BOARD_H
#define BOARD_H

#include<project.h>

// Motor Constants
    
#define STEPS_PER_CM 70.8
    
#define MIN_X_POS 0
#define MAX_X_POS 600
#define MIN_Y_POS 0
#define MAX_Y_POS 400
    
// Motor Variables
    
int16 x_pos;
int16 y_pos;
    
// Motor Functions

void move_home();
void move_x(int16 cm);
void move_y(int16 cm);

// Reed Switch Functions

char** reed_read_switches();

#endif 
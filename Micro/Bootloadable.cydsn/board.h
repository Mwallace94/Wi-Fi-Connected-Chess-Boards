#ifndef BOARD_H
#define BOARD_H

#include <project.h>
#include <stdlib.h>

// Motor Constants
    
#define STEPS_PER_MM 10
    
#define MIN_X_POS 0
#define MAX_X_POS 10000
#define MIN_Y_POS 0
#define MAX_Y_POS 10000
    
// Motor Variables

struct movement {
	int fromRow;
	int fromCol;
	int toRow;
	int toCol;
};
    
int16 x_pos;
int16 y_pos;
int16 row_square;
int16 col_square;
    
// Motor Functions

void move_home();
void move_x(int16 mm);
void move_y(int16 mm);
void limitTest();

void movepiece(struct movement move);
void moveRow(int dis);
void moveCol(int dis);
void moveColHalf(int dis);
void moveRowHalf(int dis);
void absolute_x();
void absolute_y();

// Reed Switch Variables

char board[8][12];

// Reed Switch Functions

void read_reed_switches();

#endif 
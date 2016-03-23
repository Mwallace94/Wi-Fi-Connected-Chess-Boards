#include "board.h"

void move_home() {
    Slp_1_Write(1);
    Slp_2_Write(1);
    
    uint8 x = Lim_1_Read(), y = Lim_2_Read();
    
    while(!x || !y) {    
        if(!x) {
            Dir_1_Write(0);
            Dir_2_Write(0);
            
            Stp_1_Write(0);
            CyDelayUs(50);
            Stp_1_Write(1);
            CyDelayUs(50);
            Stp_2_Write(0);
            CyDelayUs(50);
            Stp_2_Write(1);
            CyDelayUs(50);
            CyDelay(10);
        }      
        if(!y) {
            Dir_1_Write(0);
            Dir_2_Write(1);
            
            Stp_1_Write(0);
            CyDelayUs(50);
            Stp_1_Write(1);
            CyDelayUs(50);
            Stp_2_Write(0);
            CyDelayUs(50);
            Stp_2_Write(1);
            CyDelayUs(50);
            CyDelay(10);
        }
    }
    Slp_1_Write(0);
    Slp_2_Write(0);
    
    x_pos = 0;
    y_pos = 0;
}

void move_x(int16 cm) { 
    
    if(x_pos + cm > MAX_X_POS || x_pos + cm < MIN_X_POS) {
        return;
    }
    
    x_pos += cm;
    
    Slp_1_Write(1);
    Slp_2_Write(1);
    if(cm < 0) {
        Dir_1_Write(1);
        Dir_2_Write(1);
        cm *= -1;
    } else {
        Dir_1_Write(0);
        Dir_2_Write(0);
    }
    int j;
    
    for(j = 0; j < STEPS_PER_CM * cm * .5; j++) {
        Stp_1_Write(0);
        CyDelayUs(50);
        Stp_1_Write(1);
        CyDelayUs(50);
        Stp_2_Write(0);
        CyDelayUs(50);
        Stp_2_Write(1);
        CyDelayUs(50);
        CyDelay(10);
    }
    
    Slp_1_Write(0);
    Slp_2_Write(0);
}
    
void move_y(int16 cm) { 
        
    if(y_pos + cm > MAX_Y_POS || y_pos + cm < MIN_Y_POS) {
        return;
    }
    
    Slp_1_Write(1);
    Slp_2_Write(1);
    
    y_pos += cm;
    
    if(cm < 0) {
        Dir_1_Write(1);
        Dir_2_Write(0);
        cm *= -1;
    } else {
        Dir_1_Write(0);
        Dir_2_Write(1);
    }
    int j;
    
    for(j = 0; j < STEPS_PER_CM * cm * .5; j++) {
        Stp_1_Write(0);
        CyDelayUs(50);
        Stp_1_Write(1);
        CyDelayUs(50);
        Stp_2_Write(0);
        CyDelayUs(50);
        Stp_2_Write(1);
        CyDelayUs(50);
        CyDelay(10);
    }
    
    Slp_1_Write(0);
    Slp_2_Write(0);
}

char** read_reed_switches() {
    
    static char board[8][12];
    
    int i, j = 1;
    
    for(i = 0; i < 8; i++) {
        Row_Write(j);
        j = j*2;
        board[i][0] = (char) Col_1_Read();
        board[i][1] = (char) Col_2_Read();
        board[i][2] = (char) Col_3_Read();
        board[i][3] = (char) Col_4_Read();
        board[i][4] = (char) Col_5_Read();
        board[i][5] = (char) Col_6_Read();
        board[i][6] = (char) Col_7_Read();
        board[i][7] = (char) Col_8_Read();
        board[i][8] = (char) Col_9_Read();
        board[i][9] = (char) Col_10_Read();
        board[i][10] = (char) Col_11_Read();
        board[i][11] = (char) Col_12_Read();
    }
    
    return board;
    
}


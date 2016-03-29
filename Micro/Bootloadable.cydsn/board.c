#include "board.h"

void home() {
    
}
/*
void step(uint8 mm, char dir) {
    if(dir == 'F') DIR_Write(0);
    if(dir == 'B') DIR_Write(1);
    int i, j;
    for(i = 0; i < mm; i++) {
        for(j = 0; j < STEPS_PER_MM; j++) {
            STEP_Write(0);
            STEP_Write(1);
            CyDelay(5);
        }
    }
}*/

void move_home() {
    Slp_1_Write(1);
    Slp_2_Write(1);
    
    uint8 x = Lim_1_Read(), y = Lim_2_Read();
    Debug_UART_PutString("limit start");
    
    while(!x || !y) {    
        if(!y){
            Dir_1_Write(1);
            Dir_2_Write(1);
            
            Stp_1_Write(0);
            Stp_1_Write(1);
            Stp_2_Write(0);
            Stp_2_Write(1);
            CyDelay(10);
        }      
        else if(!x){
            Dir_1_Write(0);
            Dir_2_Write(1);
            
            Stp_1_Write(0);
            Stp_1_Write(1);
            Stp_2_Write(0);
            Stp_2_Write(1);
            CyDelay(10);
        }
        x = Lim_1_Read();
        y = Lim_2_Read();
        
        if(x){
         Debug_UART_PutString("limit 1 read");   
        }
        if(y){
         Debug_UART_PutString("limit 2 read");   
        }
    }
    Slp_1_Write(0);
    Slp_2_Write(0);
    
    x_pos = 0;
    y_pos = 0;
}

void limitTest() {
    Debug_UART_PutChar((char) (Lim_1_Read() + 65));
    Debug_UART_PutString(" ");
    Debug_UART_PutChar((char) (Lim_2_Read() + 65));
    Debug_UART_PutString("\n");
    CyDelay(1000);
}

void move_x(int16 mm) { 
    
    if(x_pos + mm > MAX_X_POS || x_pos + mm < MIN_X_POS) {
        return;
    }
    
    x_pos += mm;
    
    Slp_1_Write(1);
    Slp_2_Write(1);
    if(mm < 0) {
        Dir_1_Write(1);
        Dir_2_Write(1);
        mm *= -1;
    } else {
        Dir_1_Write(0);
        Dir_2_Write(0);
    }
    int j;
    
    for(j = 0; j < STEPS_PER_MM * mm * .5; j++) {
        Stp_1_Write(0);
        Stp_1_Write(1);
        Stp_2_Write(0);
        Stp_2_Write(1);
        CyDelay(10);
    }
    
    Slp_1_Write(0);
    Slp_2_Write(0);
}
    
void move_y(int16 mm) { 
        
    if(y_pos + mm > MAX_Y_POS || y_pos + mm < MIN_Y_POS) {
        return;
    }
    
    Slp_1_Write(1);
    Slp_2_Write(1);
    
    y_pos += mm;
    
    if(mm < 0) {
        Dir_1_Write(0);
        Dir_2_Write(1);
        mm *= -1;
    } else {
        Dir_1_Write(1);
        Dir_2_Write(0);
    }
    int j;
    
    for(j = 0; j < STEPS_PER_MM * mm * .5; j++) {
        Stp_1_Write(0);
        Stp_1_Write(1);
        Stp_2_Write(0);
        Stp_2_Write(1);
        CyDelay(20);
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
        board[i][0] = (char) Col_0_Read();
        board[i][1] = (char) Col_1_Read();
        board[i][2] = (char) Col_2_Read();
        board[i][3] = (char) Col_3_Read();
        board[i][4] = (char) Col_4_Read();
        board[i][5] = (char) Col_5_Read();
        board[i][6] = (char) Col_6_Read();
        board[i][7] = (char) Col_7_Read();
        board[i][8] = (char) Col_8_Read();
        board[i][9] = (char) Col_9_Read();
        board[i][10] = (char) Col_10_Read();
        board[i][11] = (char) Col_11_Read();
    }
    
    return board;
    
}


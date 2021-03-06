#include "board.h"

void move_home() {
    Slp_1_Write(1);
    Slp_2_Write(1);
    
    uint8 x = Lim_1_Read(), y = Lim_2_Read();
    
    while(!x || !y) {    
        if(!y){
            Dir_1_Write(1);
            Dir_2_Write(1);
            
            Stp_1_Write(0);
            Stp_1_Write(1);
            Stp_2_Write(0);
            Stp_2_Write(1);
            CyDelay(20);
        }      
        else if(!x){
            Dir_1_Write(0);
            Dir_2_Write(1);
            
            Stp_1_Write(0);
            Stp_1_Write(1);
            Stp_2_Write(0);
            Stp_2_Write(1);
            CyDelay(20);
        }
        x = Lim_1_Read();
        y = Lim_2_Read();
    }
    Slp_1_Write(0);
    Slp_2_Write(0);
    
    x_pos = 0;
    y_pos = 0;
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
        CyDelay(20);
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

void read_reed_switches() {
    
    Row_0_SetDriveMode(Row_0_DM_DIG_HIZ);
    Row_1_SetDriveMode(Row_1_DM_DIG_HIZ);
    Row_2_SetDriveMode(Row_2_DM_DIG_HIZ);
    Row_3_SetDriveMode(Row_3_DM_DIG_HIZ);
    Row_4_SetDriveMode(Row_4_DM_DIG_HIZ);
    Row_5_SetDriveMode(Row_5_DM_DIG_HIZ);
    Row_6_SetDriveMode(Row_6_DM_DIG_HIZ);
    Row_7_SetDriveMode(Row_7_DM_DIG_HIZ);
    
    Row_1_SetDriveMode(Row_1_DM_STRONG);
    Row_1_Write(1);
    board[0][10] = (char) Col_0_Read();
    board[0][11] = (char) Col_1_Read();
    board[0][8] = (char) Col_2_Read();
    board[0][9] = (char) Col_3_Read();
    board[0][6] = (char) Col_4_Read();
    board[0][7] = (char) Col_5_Read();
    board[0][4] = (char) Col_6_Read();
    board[0][5] = (char) Col_7_Read();
    board[0][2] = (char) Col_8_Read();
    board[0][3] = (char) Col_9_Read();
    board[0][0] = (char) Col_10_Read();
    board[0][1] = (char) Col_11_Read();
    Row_1_Write(0);
    Row_1_SetDriveMode(Row_1_DM_DIG_HIZ);

    Row_0_SetDriveMode(Row_0_DM_STRONG);
    Row_0_Write(1);
    board[1][10] = (char) Col_0_Read();
    board[1][11] = (char) Col_1_Read();
    board[1][8] = (char) Col_2_Read();
    board[1][9] = (char) Col_3_Read();
    board[1][6] = (char) Col_4_Read();
    board[1][7] = (char) Col_5_Read();
    board[1][4] = (char) Col_6_Read();
    board[1][5] = (char) Col_7_Read();
    board[1][2] = (char) Col_8_Read();
    board[1][3] = (char) Col_9_Read();
    board[1][0] = (char) Col_10_Read();
    board[1][1] = (char) Col_11_Read();
    Row_0_Write(0);
    Row_0_SetDriveMode(Row_0_DM_DIG_HIZ);

    Row_3_SetDriveMode(Row_3_DM_STRONG);
    Row_3_Write(1);
    board[2][10] = (char) Col_0_Read();
    board[2][11] = (char) Col_1_Read();
    board[2][8] = (char) Col_2_Read();
    board[2][9] = (char) Col_3_Read();
    board[2][6] = (char) Col_4_Read();
    board[2][7] = (char) Col_5_Read();
    board[2][4] = (char) Col_6_Read();
    board[2][5] = (char) Col_7_Read();
    board[2][2] = (char) Col_8_Read();
    board[2][3] = (char) Col_9_Read();
    board[2][0] = (char) Col_10_Read();
    board[2][1] = (char) Col_11_Read();
    Row_3_Write(0);
    Row_3_SetDriveMode(Row_3_DM_DIG_HIZ);
    
    Row_2_SetDriveMode(Row_2_DM_STRONG);
    Row_2_Write(1);
    board[3][10] = (char) Col_0_Read();
    board[3][11] = (char) Col_1_Read();
    board[3][8] = (char) Col_2_Read();
    board[3][9] = (char) Col_3_Read();
    board[3][6] = (char) Col_4_Read();
    board[3][7] = (char) Col_5_Read();
    board[3][4] = (char) Col_6_Read();
    board[3][5] = (char) Col_7_Read();
    board[3][2] = (char) Col_8_Read();
    board[3][3] = (char) Col_9_Read();
    board[3][0] = (char) Col_10_Read();
    board[3][1] = (char) Col_11_Read();
    Row_2_Write(0);
    Row_2_SetDriveMode(Row_2_DM_DIG_HIZ);
    
    Row_5_SetDriveMode(Row_5_DM_STRONG);
    Row_5_Write(1);
    board[4][10] = (char) Col_0_Read();
    board[4][11] = (char) Col_1_Read();
    board[4][8] = (char) Col_2_Read();
    board[4][9] = (char) Col_3_Read();
    board[4][6] = (char) Col_4_Read();
    board[4][7] = (char) Col_5_Read();
    board[4][4] = (char) Col_6_Read();
    board[4][5] = (char) Col_7_Read();
    board[4][2] = (char) Col_8_Read();
    board[4][3] = (char) Col_9_Read();
    board[4][0] = (char) Col_10_Read();
    board[4][1] = (char) Col_11_Read();
    Row_5_Write(0);
    Row_5_SetDriveMode(Row_5_DM_DIG_HIZ);
    
    Row_4_SetDriveMode(Row_4_DM_STRONG);
    Row_4_Write(1);
    board[5][10] = (char) Col_0_Read();
    board[5][11] = (char) Col_1_Read();
    board[5][8] = (char) Col_2_Read();
    board[5][9] = (char) Col_3_Read();
    board[5][6] = (char) Col_4_Read();
    board[5][7] = (char) Col_5_Read();
    board[5][4] = (char) Col_6_Read();
    board[5][5] = (char) Col_7_Read();
    board[5][2] = (char) Col_8_Read();
    board[5][3] = (char) Col_9_Read();
    board[5][0] = (char) Col_10_Read();
    board[5][1] = (char) Col_11_Read();
    Row_4_Write(0);
    Row_4_SetDriveMode(Row_4_DM_DIG_HIZ);
    
    Row_7_SetDriveMode(Row_7_DM_STRONG);
    Row_7_Write(1);
    board[6][10] = (char) Col_0_Read();
    board[6][11] = (char) Col_1_Read();
    board[6][8] = (char) Col_2_Read();
    board[6][9] = (char) Col_3_Read();
    board[6][6] = (char) Col_4_Read();
    board[6][7] = (char) Col_5_Read();
    board[6][4] = (char) Col_6_Read();
    board[6][5] = (char) Col_7_Read();
    board[6][2] = (char) Col_8_Read();
    board[6][3] = (char) Col_9_Read();
    board[6][0] = (char) Col_10_Read();
    board[6][1] = (char) Col_11_Read();
    Row_7_Write(0);
    Row_7_SetDriveMode(Row_7_DM_DIG_HIZ);
    
    Row_6_SetDriveMode(Row_6_DM_STRONG);
    Row_6_Write(1);
    board[7][10] = (char) Col_0_Read();
    board[7][11] = (char) Col_1_Read();
    board[7][8] = (char) Col_2_Read();
    board[7][9] = (char) Col_3_Read();
    board[7][6] = (char) Col_4_Read();
    board[7][7] = (char) Col_5_Read();
    board[7][4] = (char) Col_6_Read();
    board[7][5] = (char) Col_7_Read();
    board[7][2] = (char) Col_8_Read();
    board[7][3] = (char) Col_9_Read();
    board[7][0] = (char) Col_10_Read();
    board[7][1] = (char) Col_11_Read();
    Row_6_Write(0);
    Row_6_SetDriveMode(Row_6_DM_DIG_HIZ);
}
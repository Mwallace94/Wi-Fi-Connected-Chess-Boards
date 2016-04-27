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
    }
    Slp_1_Write(0);
    Slp_2_Write(0);
    
    x_pos = 0;
    y_pos = 0;
    
    col_square = 11;
    row_square = 0;
    
    move_x(37);
    move_y(15);
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
        CyDelay(10);
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

void moveCol(int dis) {
    move_x(51 * dis);
}

void moveRow(int dis) {
    move_y(51 * dis * -1);
}

void moveRowHalf(int dis) {
    move_y((int)(25.5 * dis * -1));
}

void moveColHalf(int dis) {
    move_x((int)(25.5 * dis));
}

void graveyard(struct movement move) {
 
    if(board[move.toRow][move.toCol] == 1) {
        struct movement move2;
        move2.fromCol = move.toCol;
        move2.fromRow = move.toRow;
        for(int i = 10; i < 12; i++) {
            for(int j = 0; j < 7; j++) {
                if (board[j][i] == 0) {
                    move2.toCol = i;
                    move2.toRow = j;
                    movepiece(move2);
                    read_reed_switches();
                    return;
                }
            }
        }
    }
}

void movepiece(struct movement move) {
    
    if(move.toCol > 11 || move.toCol < 0 || move.toRow < 0 || move.toRow > 7) return; 
    
    graveyard(move);
    
    moveRow(row_square - move.fromRow);
    moveCol(col_square - move.fromCol);
    
    row_square = move.toRow;
    col_square = move.toCol;
    
    CyDelay(1000);

    Em_Write(1);
    
    int rowdis = move.fromRow - move.toRow;
    int coldis = move.fromCol - move.toCol;
    /*
    //diagnal movement if clear path
    if (abs(rowdis) == abs(coldis)) {
        int temp = 0;
        for(int i = 1; i <= abs(coldis); i++) {
            if (board[move.fromRow + i * rowdis / abs(coldis)][move.fromCol + i * coldis / abs(coldis)] != 0) temp++;
        }
        if (temp == 0) {
            for(int i = 0; i < abs(coldis) * 51; i++) {
                move_x(coldis / abs(coldis));
                move_y(rowdis / abs(rowdis) * -1);
            }
        }
        
        absolute_x();
        absolute_y();
    
        Em_Write(0);
        return;
    }
    */
    //col movement if clear path
    if (rowdis == 0) {
        int temp = 0;
        for(int i = 1; i <= abs(coldis); i++) {
            if (board[move.fromRow][move.fromCol + i * coldis / abs(coldis) * -1] != 0) temp++;
        }
        if (temp != 0) {
            temp++;
        } else {
            moveCol(coldis);
            
            absolute_x();
            absolute_y();
        
            Em_Write(0);
            return;
        }
    }

    //row movement if clear path
    if (coldis == 0) {
        int temp = 0;
        for(int i = 1; i <= abs(rowdis); i++) {
            if (board[move.fromRow + i * rowdis / abs(rowdis) * -1][move.fromCol] != 0) temp++;
        }
        if( temp != 0) {
            temp++;
        } else {
            moveRow(rowdis);
            
            absolute_x();
            absolute_y();
        
            Em_Write(0);
            return;
        }
    }

    //up or down indicator for end adjustment, where down is 1 and up -1
    //left or right indicator for end adjustment, where left is -1 and right is 1       
    int uod = 0, lor = 0;

    //determines the best path between spaces for cols

    if (move.fromCol < move.toCol) {
        lor = 1;
    } else if (move.fromCol > move.toCol) {
        lor = -1;
    } else if (move.fromCol < 6) {
        lor = 1;
    } else {
        lor = -1;
    }
    moveColHalf(lor * -1);

    //determines the best path between spaces for rows
    if (move.fromRow > move.toRow) {
        uod = -1;
    } else if (move.fromRow < move.toRow) {
        uod = 1;
    } else if (move.toRow < 4) {
        uod = -1;
    } else {
        uod = 1;
    }

    //moves across the rows with the adjustment
    if (rowdis == 0) {
        moveRowHalf(uod);
    } else if (rowdis > 0) {
        moveRowHalf(rowdis / abs(rowdis) * (rowdis * 2 - uod * -1));
    } else {
        moveRowHalf(rowdis / abs(rowdis) * (abs(rowdis) * 2 - uod));
    }
    //moves across the rows
    if (coldis == 0) {
        moveColHalf(lor);
    } else if (coldis > 0) {
        moveColHalf(coldis / abs(coldis) * (coldis * 2 - lor * -1));
    } else {
        moveColHalf(coldis / abs(coldis) * (abs(coldis) * 2 - lor));
    }

    //moves row adjustment
    moveRowHalf(-1 * uod);
    
    absolute_x();
    absolute_y();
    
    Em_Write(0);
    
}

void absolute_x() {
    int absX = 599 - (51 * col_square) - (row_square / 3);
    move_x(absX - x_pos);
}

void absolute_y() {
    int absY = 15 + 3 * ((11 - col_square) / 4);
    int temp = (11 - col_square) / 4;
    int temp1 = (int) ((51.3 - (((float) temp) * .4)) * ((float) row_square));
    absY = absY + temp1;
    move_y(absY - y_pos);
}
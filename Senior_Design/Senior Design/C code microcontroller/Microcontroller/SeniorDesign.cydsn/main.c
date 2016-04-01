#include "main.h"
#include <stdlib.h>

int main() {
    
    init();
    
    while(1) {
        
    read_reed_switches();
    CyDelay(2000);
    }
    //uint8 lim1 = Lim_1_Read();
    /*
    while(1) {
        limitTest();
    }
    */
    //turns em on and off and calibrates it
    /*
    Em_Write(1);
    Debug_UART_PutString("electromagnet on");
    move_home();
    Debug_UART_PutString("gantry homed");
    move_x(5);
    move_y(5);
    
    while(1)
    {
        move_x(5);
        move_y(5);
        move_x(-5);
        move_y(-5);
    }
    */
    
    /*
    //commands
    while(1) {
        char message[8];
        uint8 i, j = 0;
        uint8 temp = 0;
        while(temp < 1) {
            temp = Debug_UART_GetRxBufferSize();
        }
        message[j] = (char) Debug_UART_GetByte();
        while(message[j++] != '\r' && j < 8) {
            uint8 temp = 0;
            while(temp < 1) {
                temp = Debug_UART_GetRxBufferSize();
            }
            message[j] = (char) Debug_UART_GetByte();
        }
        for(i = 0; i < j; i++) {
            //Debug_UART_PutChar(message[i]);
        }
        char num[4];
        switch (message[0]) {
            case 'x' :
                Debug_UART_PutChar(message[0]);
                if(j > 2) {
                    for(i = 3; i < j; i++) {
                        num[i-3] = message[i];
                    }
                    Debug_UART_PutChar(atoi(num));
                    if(message[2] == '-') {
                        move_x((int16) (atoi(num)*-1));
                    } else {
                        move_x((int16) (atoi(num)));
                    }
                }
                break;  
            case 'y' :
                Debug_UART_PutChar(message[0]);
                if(j > 2) {
                    for(i = 3; i < j; i++) {
                        num[i-3] = message[i];
                    }
                    Debug_UART_PutChar(atoi(num));
                    if(message[2] == '-') {
                        move_y((int16) (atoi(num)*-1));
                    } else {
                        move_y((int16) (atoi(num)));
                    }
                }
                break;  
            case 'h' :
                Debug_UART_PutChar(message[0]);
                move_home();
                break;
            case 'e' :
                Debug_UART_PutChar(message[0]);
                if(message[2] == 'o' && message[3] == 'n') {
                    Debug_UART_PutString("on");
                    Em_Write(1);
                } else {
                    Debug_UART_PutString("off");
                    Em_Write(0);
                }
                break;
            default :
                break;
        }   
    }
    */
    
    //calibrates and moves x exclusively
    /*Em_Write(1);
    Debug_UART_PutString("em on");
    move_home();
    if(x_pos != 0 || y_pos != 0){
       Debug_UART_PutString("Not successfully calibrated");
    }else{
        move_x(1);
        uint8 x = Lim_1_Read();
        uint8 y = Lim_2_Read();
        if(!x && y){
          Debug_UART_PutString("x successfully moved");
        }else{
          Debug_UART_PutString("exclusive x failed");
        }
        move_home();  
    }
    Em_Write(0);
    Debug_UART_PutString("em off");
    */
    
    //calibrates and moves y exclusively
    /*Em_Write(1);
    Debug_UART_PutString("em on");
    move_home();
    if(x_pos != 0 || y_pos != 0){
       Debug_UART_PutString("Not successfully calibrated");
    }else{
        move_y(1);
        uint8 x = Lim_1_Read();
        uint8 y = Lim_2_Read();
        if(x && !y){
          Debug_UART_PutString("x successfully moved");
        }else{
          Debug_UART_PutString("exclusive x failed");
        }
        move_home();  
    }
    Em_Write(0);
    Debug_UART_PutString("em off");
    */
    
    //moves x and y by 20
    /*
    Em_Write(1);
    Debug_UART_PutString("em on");
    int16 init_x = x_pos;
    int16 init_y = y_pos;
    move_x(20);
    move_y(20);
    if(x_pos == init_x + 20 && x_pos == init_y + 20){
       Debug_UART_PutString("successfully moved x and y");
    }else{
       Debug_UART_PutString("unsuccessfully moved x and y");   
    }
    Em_Write(0);
    Debug_UART_PutString("em on");
    */
    
    /*
    x_pos = 0;
    y_pos = 0;

    while (1) {
        
        Debug_UART_PutString("x20");
        move_x(20);
        
        CyDelay(1000);
        
        Debug_UART_PutString("x-20");
        move_x(-20);
        
        CyDelay(1000);
        
        Debug_UART_PutString("y20");
        move_y(20);
        
        CyDelay(1000);
        
        Debug_UART_PutString("y-20");
        move_y(-20);
        
        CyDelay(1000);
        
        }
            //Debug_UART_PutString("tick\n");
 */
}

void init() {
    CyGlobalIntEnable;
    
    Bootloader_Start();
    
    Debug_UART_Start();
    Debug_UART_PutString("CSE 4940: Wireless Chess Board\n\n");
    
    Esp_UART_Start();
    
    LCD_Start();
}

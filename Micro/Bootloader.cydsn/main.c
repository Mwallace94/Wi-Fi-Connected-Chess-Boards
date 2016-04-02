#include "main.h"

int main() {
    
    init();
    
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
}

void init() {
    CyGlobalIntEnable;
    
    Bootloader_Start();
    
    Debug_UART_Start();
    Debug_UART_PutString("CSE 4940: Wireless Chess Board\n\n");
    
    Esp_UART_Start();
    
    LCD_Start();
}

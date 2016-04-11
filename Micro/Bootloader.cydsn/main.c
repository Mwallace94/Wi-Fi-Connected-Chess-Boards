#include "main.h"

int main() {
    
    init();
    
    while(1) {

        debug();
        
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

void debug() {

    char message[8] = "";
    char temp;
    char length;

    if(Debug_UART_GetRxBufferSize > 0) {

        for(int i = 0; (temp = Debug_UART_GetChar()) != '\r'; i++) {
            Debug_UART_PutChar(temp);
            message[i] = temp;
        }

        Debug_UART_PutChar('\r');
        Debug_UART_ClearRxBuffer();

        length = strlen(message);

        char num[4];
        switch(message[0]) {
            case 'x':
                if(length > 3) {
                    for(int i = 3; i < length; i++) {
                        num[i - 3] = message[i];
                    }
                    if(message[2] == '-') {
                        move_x((int16) (atoi(num)*-1));
                    } else {
                        move_x((int16) (atoi(num)));
                    }
                }
                break;
            case 'y' :
                if(length > 3) {
                    for(int i = 3; i < length; i++) {
                        num[i - 3] = message[i];
                    }
                    if(message[2] == '-') {
                        move_y((int16) (atoi(num)*-1));
                    } else {
                        move_y((int16) (atoi(num)));
                    }
                }
                break;
            case 'h':
                move_home();
                Debug_UART_PutString("moving home\n");
                break;
            case 'e':
                if(message[2] == 'o' && message[3] == 'n') {
                    Em_Write(1);
                    Debug_UART_PutString("magnet now on\n");
                } else {
                    Em_Write(0);
                    Debug_UART_PutString("magnet now off\n");
                }
                break;
            case 'r':
                read_reed_switches();
                for(int i = 0; i < 8; i++) {
                    for(int j = 0; j < 12; j++) {
                        char on[3];
                        on[0] = on[2] = ' ';
                        on[1] = board[i][j] + 48;
                        Debug_UART_PutString(on);
                    }
                    Debug_UART_PutString("\n\r");
                }
                break;
            case 'l':
                Debug_UART_PutChar((char) (Lim_1_Read() + 65));
                Debug_UART_PutString(" ");
                Debug_UART_PutChar((char) (Lim_2_Read() + 65));
                Debug_UART_PutString("\n");
                break;
            default:
                break;
        }
    }
    
}
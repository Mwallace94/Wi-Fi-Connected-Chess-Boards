#include "main.h"

int main() {
    
    init();
    
    while(1) {

        debug();
        
        /*
        if(Esp_UART_GetRxBufferSize() > 0) {
            Debug_UART_PutChar(Esp_UART_GetChar());
        }
        if(Debug_UART_GetRxBufferSize() > 0) {
            char temp = Debug_UART_GetChar();
            Debug_UART_PutChar(temp);
            Esp_UART_PutChar(temp);
        }
        
        
        Esp_UART_PutString("AT\n\n");
        CyDelay(5000);
        Debug_UART_PutChar(Esp_UART_GetChar());
        */
    }
}

void init() {
    CyGlobalIntEnable;
    
    Bootloader_Start();
    
    Debug_UART_Start();
    Debug_UART_PutString("CSE 4940: Wireless Chess Board\r\n\r\n");
    
    Esp_UART_Start();
    
    LCD_Start();
}

void debug() {

    char message[64] = "";
    char temp;
    char length;

    if(Debug_UART_GetRxBufferSize() > 0) {

        for(int i = 0; (temp = Debug_UART_GetChar()) != '\r'; i++) {
            Debug_UART_PutChar(temp);
            message[i] = temp;
            while(Debug_UART_GetRxBufferSize() == 0);
        }

        Debug_UART_PutChar('\r');
        Debug_UART_PutChar('\n');
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
                Debug_UART_PutString("moving home\r\n");
                break;
            case 'e':
                if(message[2] == 'o' && message[3] == 'n') {
                    Em_Write(1);
                    Debug_UART_PutString("magnet now on\r\n");
                } else {
                    Em_Write(0);
                    Debug_UART_PutString("magnet now off\r\n");
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
                    Debug_UART_PutString("\r\n");
                }
                break;
            case 'l':
                Debug_UART_PutChar((char) (Lim_1_Read() + 65));
                Debug_UART_PutString(" ");
                Debug_UART_PutChar((char) (Lim_2_Read() + 65));
                Debug_UART_PutString("\r\n");
                break;
            case 'w':
                if(message[2] == 'w') {
                    Esp_UART_PutString(message + 4);
                }
                if(message[2] == 'r') {
                    int mSize = Esp_UART_GetRxBufferSize();
                    for (int i = 0; i < mSize; i++) {
                        message[i] = Esp_UART_GetChar();
                    }
                    Debug_UART_PutString(message);
                    Debug_UART_PutString("\r\n");
                }
                break;
            default:
                break;
        }
    }
    
}
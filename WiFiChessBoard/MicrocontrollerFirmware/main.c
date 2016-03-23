#include "main.h"

int main() {
    
    init();
    
    x_pos = 0;
    y_pos = 0;
    
    move_x(30);

    /*
    while (1) {
        
        Debug_UART_PutString("x20\n");
        move_x(30);
        
        CyDelay(1000);
        
        Debug_UART_PutString("y20\n");
        move_y(30);
        
        CyDelay(1000);
        
        Debug_UART_PutString("x-20\n");
        move_x(-30);
        
        CyDelay(1000);
        
        Debug_UART_PutString("y-20\n");
        move_y(-30);
        
        CyDelay(1000);
        
        }
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

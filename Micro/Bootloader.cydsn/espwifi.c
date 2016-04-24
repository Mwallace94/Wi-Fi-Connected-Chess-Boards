/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "espwifi.h"


static char blank[9] = "";

    char* esp_transmit(char* msg, char* numBytes) {
        char* temp;
        Esp_UART_PutString("AT+CIPSTART=\"TCP\",\"192.168.173.1\",666\r\n");
        temp = esp_helper(1000);
        if (strcmp(temp, "") != 0) return temp;
        Esp_UART_PutString("AT+CIPSEND=");
        temp = esp_helper(100);
        if (strcmp(temp, "") != 0) return temp;
        Esp_UART_PutString(numBytes);
        temp = esp_helper(100);
        if (strcmp(temp, "") != 0) return temp;
        Esp_UART_PutString("\r\n");
        temp = esp_helper(1000);
        if (strcmp(temp, "") != 0) return temp;
        for(int i = 0; i < atoi(numBytes); i++) {
            Esp_UART_PutChar(msg[i]);
        }
        Esp_UART_PutString(msg);
        return esp_helper(2500);
    }
    
    char* esp_helper(uint32 time) {
        CyDelay(time);
        uint8 size = Esp_UART_GetRxBufferSize();
        Debug_UART_PutChar(size + 48);
        uint8 temp = size;
        char msg[size];
        strcpy(recv, blank);
        
        for(int i = 0; i < size; i++) {
            if (strstr(msg, "+IPD,") != NULL) {
                msg[i] = Esp_UART_GetChar();
                Debug_UART_PutChar(msg[i]);
                temp = msg[i] - 48;
                Esp_UART_GetChar();
                Debug_UART_PutString("\n\r!");
                for(int j = 0; j < temp; j++) {
                    recv[j] = Esp_UART_GetChar();
                }
                return recv;
                    
            } else {
                msg[i] = Esp_UART_GetChar();
                Debug_UART_PutChar(msg[i]);
            }
        }
        return recv;

    }
        
/* [] END OF FILE */
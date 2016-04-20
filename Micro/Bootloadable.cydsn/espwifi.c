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
#include <string.h>

static char recv[9];
static char blank[9] = "";

    char* esp_transmit(char* msg, char* numBytes) {
        Esp_UART_PutString("AT+CIPSTART=\"TCP\",\"192.168.173.1\",666\r\n");
        esp_helper();
        Esp_UART_PutString("AT+CIPSEND=");
        esp_helper();
        Esp_UART_PutString(numBytes);
        esp_helper();
        Esp_UART_PutString("\r\n");
        esp_helper();
        Esp_UART_PutString(msg);
        return esp_helper();
    }
    
    char* esp_helper() {
        uint8 size = Esp_UART_GetRxBufferSize();
        uint8 temp = size;
        char msg[size];
        strcpy(recv, blank);
        
        for(int i = 0; i < size; i++) {
            if (strstr(msg, "+IPD,") != NULL) {
                msg[i] = Esp_UART_GetChar();
                temp = msg[i] - 48;
                Esp_UART_GetChar();
                for(int j = 0; j < temp; j++) {
                    recv[j] = Esp_UART_GetChar();
                }
                return recv;
                    
            } else {
                msg[i] = Esp_UART_GetChar();
            }
        }
        return recv;

    }
        
/* [] END OF FILE */
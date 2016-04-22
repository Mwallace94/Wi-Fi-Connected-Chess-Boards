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
#ifndef ESPWIFI_H
#define ESPWIFI_H
    
#include <string.h>
#include <project.h>

static char recv[9];

    char* esp_transmit(char* msg, char* numBytes);  
    char* esp_helper(uint32 time);

#endif
    
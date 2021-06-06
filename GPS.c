#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tm4c123gh6pm.h"

#define GPS_UART_D UART2_DR_R
#define GPS_UART_F UART2_FR_R

char mask[6];
char target[6] = {'G','P','G','G','A',','};
char temp0[6];
char temp1d[2],temp1m[8];
char temp2d[3],temp2m[8];
char gps_fix,dummy;

char gps_fetch(double* new_lat,double* new_lon,double* new_time){
        int i,pass=0;
        while(!pass){
            while((GPS_UART_F & 0x10) != 0){};
            if(GPS_UART_D == '$'){
                pass = 1;
                for(i=0;i<6;i++){
                    while((GPS_UART_F & 0x10) != 0){};
                    mask[i] = GPS_UART_D;
                    if(mask[i]!=target[i]) pass = 0;
                }
            }
        }
        for(i = 0; i <6;i++){
            while((GPS_UART_F & 0x10) != 0){};
            temp0[i] = GPS_UART_D;
        }
        for(i = 0; i <4;i++){
            while((GPS_UART_F & 0x10) != 0){};
            dummy = GPS_UART_D;
        }
        for(i = 0; i <2;i++){
            while((GPS_UART_F & 0x10) != 0){};
            temp1d[i] = GPS_UART_D;
        }
        for(i = 0; i <8;i++){
            while((GPS_UART_F & 0x10) != 0){};
            temp1m[i] = GPS_UART_D;
        }
        for(i = 0; i <3;i++){
            while((GPS_UART_F & 0x10) != 0){};
            dummy = GPS_UART_D;
        }
        for(i = 0; i <3;i++){
            while((GPS_UART_F & 0x10) != 0){};
            temp2d[i] = GPS_UART_D;
        }
        for(i = 0; i <8;i++){
            while((GPS_UART_F & 0x10) != 0){};
            temp2m[i] = GPS_UART_D;
        }
        for(i = 0; i <3;i++){
            while((GPS_UART_F & 0x10) != 0){};
            dummy = GPS_UART_D;
        }
        {
            while((GPS_UART_F & 0x10) != 0){};
            gps_fix = GPS_UART_D;
        }

        *new_time = atoi(temp0);
        *new_lat = atoi(temp1d);
        *new_lat = *new_lat + (atof(temp1m))/60;
        *new_lon = atoi(temp2d);
        *new_lon = *new_lon + (atof(temp2m))/60;

        return gps_fix;
}

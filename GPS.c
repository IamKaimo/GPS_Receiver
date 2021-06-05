#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tm4c123gh6pm.h"

#define GPS_UART_D UART2_DR_R
#define GPS_UART_F UART2_FR_R
#define PI 3.14159265

char mask[6];
char target[6] = {'G','P','G','G','A',','};
char data[40];
char temp1d[2],temp1m[8];
char temp2d[3],temp2m[8];
char temp3[6];
char gps_fix;

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
        for(i = 0; i <40;i++){
            while((GPS_UART_F & 0x10) != 0){};
            data[i] = GPS_UART_D;
        }

        strncpy(temp3, data, 6);
        strncpy(temp1d, data+  10, 2);
        strncpy(temp1m, data + 12, 8);
        strncpy(temp2d, data + 23, 3);
        strncpy(temp2m, data + 26, 8);
        gps_fix =  data[37];

        *new_lat = atoi(temp1d);
        *new_lat = *new_lat + (atof(temp1m))/60;
        *new_lon = atoi(temp2d);
        *new_lon = *new_lon + (atof(temp2m))/60;
        *new_time = atoi(temp3);
        return gps_fix;
}
void dec_to_dms(double dec,double* arr){
    arr[1]= dec - (int)dec;
    arr[0]= dec - arr[1];
    arr[1] = arr[1] * 60;
    arr[2] = arr[1] - (int)arr[1];
    arr[1] = arr[1] - arr[2];
    arr[2]= arr[2] * 60;
}
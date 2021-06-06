#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include "TIVA.h"
#include "LCD.h"
#include "GPS.h"
#include "Utilities.h"

int pointer = 0;
double latitude,longitude,time=0;
double data_log[100][3];

int main(void){
    Initialize();
    Red_LED(1);
    while(1){ //program loop
        gps_fetch(&latitude,&longitude,&time);
        data_log[pointer][0] = latitude;
        data_log[pointer][1] = longitude;
        data_log[pointer][2] = time;
        pointer++;
    }   //end program loop
}   //end main

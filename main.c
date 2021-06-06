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
double total_distance = 0;
char dist[4];

int main(void){
    Initialize();
    lcd_send_cmd(1);
    while(1){ //program loop
        check_distance(total_distance); // Turn LED On if distance < 100
        int_to_str(total_distance,dist);
        display_2d("Distance is:",dist);//  Display the two strings
    }   //end program loop
}   //end main

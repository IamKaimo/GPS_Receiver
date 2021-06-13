#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tm4c123gh6pm.h"
#include "TIVA.h"
#include "LCD.h"
#include "GPS.h"
#include "KEYPAD.h"
#include "SYSTICK.h"
#include "Utilities.h"

int fetch_no = 0,pointer = 0;
double latitude,longitude,time=0;
double distance=0,total_distance=0;
int  target_distance = 0;
double data_log[500][3];
char data1[16] = {'D','i','s','t','a','n','c','e',':',' ',' ',' ',' ','m','e','t'};
char data2[16] = {'T','i','m','e',' ',' ',' ',' ',':',' ',' ',' ',' ','s','e','c'};
char start = 0,end = 0,temp,check;
char output[14];
char key=0,pass = 0,index = 0;
char dist[4] = {' ',' ',' ',' '};
int v= 0;

void KeyPad_Handler(void){
    key = getChar2();
    if(key == '#'){
    start = 0;
    end = 1;
    }
    Delay(10000);
    GPIO_PORTB_ICR_R = 0x0F; // clear flag4
    Delay(10000);
}


int main(void){
     Initialize();  //Initialize Ports,UART,and LCD
     while(1){      //program loop
       if(!start && !end){
           lcd_send_cmd(1);
           display_2d("Press * To Start","Press # To Stop");
           while(key != '*') {key = getChar(); Delay(5000);}
           Delay(400000);
           lcd_send_cmd(1);
           index = 0,pass = 0,key = 0;
           while(!pass){
               display_2d("Enter Distance:",dist);
               lcd_set_cursor(2,index);
               key = getChar();
               if(key >=48 && key <=57){
                   dist[index] = key;
                   if(index <3)index++;
               }
               else if(key =='*'){
                   pass = 1; start = 1;
                   target_distance = atoi(dist);
                   GPIO_PORTB_IM_R |= 0x0F; // arm interrupt on PF4
                   GPIO_PORTB_ICR_R = 0x0F;
               }
               else if(key == '#'){
                   if(index == 3 && dist[index]!=' ')dist[index]=' ';
                   else if(index == 0) pass = 1;
                   else {dist[index-1]=' '; index--;}
               }
               key = 0;
               Delay(400000);
           }
       }
       else if(start){
           check_distance(total_distance,target_distance);
           if(gps_fetch(&latitude,&longitude,&time) == '1'){
               fetch_no++;
               if(!pointer){
                   data_log[0][0] = latitude;
                   data_log[0][1] = longitude;
                   data_log[0][2] = time;
                   pointer++;
               }
               else{
                   distance = calc_distance(latitude,longitude,data_log[pointer - 1][0],data_log[pointer - 1][1]);
                   if(distance > 1){
                       data_log[pointer][0] = latitude;
                       data_log[pointer][1] = longitude;
                       data_log[pointer][2] = time;
                       total_distance+= distance;
                       pointer++;
                       snprintf(output, 20, "%.10lf", latitude);
                   }
               }
               int_to_str(total_distance,data1 + 9);
               int_to_str(fetch_no,data2 + 9); //need maintenance
               display_2d(data1,data2);
           }
           else{
               char a[16] = {'W','a','i','t','i','n','g',' ','f','o','r',' ',' ',' ',' ',' '};
               char b[16] = {'G','P','S',' ','S','i','g','n','a','l','.','.',' ',' ',' ',' '};
               display_2d(a,b);
           }

      }
       else if(end)
       {
           GPIO_PORTB_IM_R &= ~0x0F; // arm interrupt on PF4
           lcd_send_cmd(1);
           display_2d("Send U Letter to","start transfer.");
           int i,index;
           check = 'n';
           Delay(50000);
           while (check != 'U'){
               while((UART0_FR_R & 0x10) != 0){};
               check = UART0_DR_R;
           }
           for(i=0;i<pointer;i++){
               snprintf(output, 20, "%.10lf", data_log[i][0]);
               index = 0;
               while(output[index] != NULL){
                   while((UART0_FR_R & 0x20) != 0){};
                   UART0_DR_R = output[index];
                   index++;
               }
               while((UART0_FR_R & 0x20) != 0){};
               UART0_DR_R = '\n';
               snprintf(output, 20, "%.10lf", data_log[i][1]);
               index = 0;
               while(output[index] != NULL){
                   while((UART0_FR_R & 0x20) != 0){};
                   UART0_DR_R = output[index];
                   index++;
               }
               while((UART0_FR_R & 0x20) != 0){};
               UART0_DR_R = '\n';
           }
           while((UART0_FR_R & 0x20) != 0){};
           UART0_DR_R = 'E';
           start = 0;
           end = 0;
           total_distance = 0;
           pointer = 0;
           check ='n';
           fetch_no = 0;
           dist[0] = ' ',dist[1] = ' ',dist[2] = ' ',dist[3] = ' ';
           check_distance(total_distance,target_distance);
           for(i=0;i<4;i++){
               data1[9+i]=' ';
               data2[9+i]=' ';
           }
       }
    }   //end program loop
}   //end main

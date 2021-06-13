#include <Utilities.h>
#include "tm4c123gh6pm.h"
#define data_sent GPIO_PORTB_DATA_R
#define configure GPIO_PORTA_DATA_R
#define RS 2
#define EN 3

void lcd_send_cmd(char cmd){
    configure &= ~(1<<RS);     //RS=0 for sending command
    data_sent = (cmd & 0xF0) | (data_sent & 0x0F); // MS 4 bits
    configure |= 1 << EN;  //setting EN to high
    Delay(3000);
    configure &= ~(1<<EN); //setting EN to low
    Delay(3000);
    data_sent = (cmd <<4) | (data_sent & 0x0F);
    configure |= 1 << EN;  //setting EN to high
    Delay(3000);
    configure &= ~(1<<EN); //setting EN to low
}
void lcd_init (void){
   // lcd_send_cmd(0x20); //DL=1(8 bit mode),N = 1(2 line display),F = 0 (5x8 characters)
    //Delay(10000);
    lcd_send_cmd(0x28);
    Delay(3000);
    lcd_send_cmd(0x0F); //Display on
    Delay(3000);
    lcd_send_cmd(0x01);  //Display clear
    Delay(3000);
    lcd_send_cmd(0x06); //I/D=1,S=0
}
void display_data (char* data){
    char i = 0;
    while(data[i] != '\0'){
        configure |= 1<<RS;     //RS=1 for sending data
                data_sent = (data[i] & 0xF0) | (data_sent & 0x0F);
                configure |= 1 << EN;  //setting EN to high
                Delay(3000);
                configure &= ~(1<<EN); //setting EN to low
                Delay(3000);
        data_sent = (data[i] << 4) | (data_sent & 0x0F);
        configure |= 1 << EN;  //setting EN to high
        Delay(3000);
        configure &= ~(1<<EN); //setting EN to low
        i++;
    }
}
void lcd_set_cursor(char row, char col){
    if(row) col |= 0xC0;
    else    col |= 0x80;
    lcd_send_cmd(col);
}

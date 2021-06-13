#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tm4c123gh6pm.h"
#include "Utilities.h"
char row,col,shift;
long temp_key;
//B Input
//E Output

char getChar()
{
    row = 1,col = 1,shift = 0x02;
    while(!(GPIO_PORTB_DATA_R & 0x0F)){}
    temp_key = GPIO_PORTB_DATA_R;
    if((temp_key & 0x01) != 0)
    {
        GPIO_PORTE_DATA_R &= ~0x02;
        temp_key = GPIO_PORTB_DATA_R;
       while((temp_key & 0x0F))
        {
            GPIO_PORTE_DATA_R |= shift;
            shift = shift<<1;
            GPIO_PORTE_DATA_R &= ~shift;
            col++;
            temp_key = GPIO_PORTB_DATA_R;
        }
        GPIO_PORTE_DATA_R |= shift;
    }
    else if((temp_key & 0x02) != 0)
    {
       row = 2;
       GPIO_PORTE_DATA_R &= ~0x02;
       temp_key = GPIO_PORTB_DATA_R;
         while(temp_key & 0x0F)
         {
           GPIO_PORTE_DATA_R |= shift;
           shift = shift<<1;
           GPIO_PORTE_DATA_R &= ~shift;
           col++;
           temp_key = GPIO_PORTB_DATA_R;
         }
         GPIO_PORTE_DATA_R |= shift;
    }
    else if((temp_key & 0x04) != 0)
        {
           row = 3;
           GPIO_PORTE_DATA_R &= ~0x02;
           temp_key = GPIO_PORTB_DATA_R;
             while(temp_key & 0x0F)
             {
               GPIO_PORTE_DATA_R |= shift;
               shift = shift<<1;
               GPIO_PORTE_DATA_R &= ~shift;
               col++;
               temp_key = GPIO_PORTB_DATA_R;
             }
             GPIO_PORTE_DATA_R |= shift;

        }
    else if((temp_key & 0x08) != 0)
        {
           row = 4;
           GPIO_PORTE_DATA_R &= ~0x02;
           temp_key = GPIO_PORTB_DATA_R;
             while(temp_key & 0x0F)
             {
               GPIO_PORTE_DATA_R |= shift;
               shift = shift<<1;
               GPIO_PORTE_DATA_R &= ~shift;
               col++;
               temp_key = GPIO_PORTB_DATA_R;
             }
             GPIO_PORTE_DATA_R |= shift;
        }
    switch(col + 3*(row-1))
    {
        case 1:return '1';
        case 2:return '2';
        case 3:return '3';
        case 4:return '4';
        case 5:return '5';
        case 6:return '6';
        case 7:return '7';
        case 8:return '8';
        case 9:return '9';
        case 10:return '*';
        case 11:return '0';
        case 12:return '#';
        default: return 0;
    }
}
char getChar2()
{
    row = 1,col = 1,shift = 0x02;
    Delay(1000);
    temp_key = GPIO_PORTB_DATA_R;
    if((temp_key & 0x01) != 0)
    {
        GPIO_PORTE_DATA_R &= ~0x02;
        temp_key = GPIO_PORTB_DATA_R;
       while((temp_key & 0x0F))
        {
            GPIO_PORTE_DATA_R |= shift;
            shift = shift<<1;
            GPIO_PORTE_DATA_R &= ~shift;
            col++;
            temp_key = GPIO_PORTB_DATA_R;
        }
        GPIO_PORTE_DATA_R |= shift;
    }
    else if((temp_key & 0x02) != 0)
    {
       row = 2;
       GPIO_PORTE_DATA_R &= ~0x02;
       temp_key = GPIO_PORTB_DATA_R;
         while(temp_key & 0x0F)
         {
           GPIO_PORTE_DATA_R |= shift;
           shift = shift<<1;
           GPIO_PORTE_DATA_R &= ~shift;
           col++;
           temp_key = GPIO_PORTB_DATA_R;
         }
         GPIO_PORTE_DATA_R |= shift;
    }
    else if((temp_key & 0x04) != 0)
        {
           row = 3;
           GPIO_PORTE_DATA_R &= ~0x02;
           temp_key = GPIO_PORTB_DATA_R;
             while(temp_key & 0x0F)
             {
               GPIO_PORTE_DATA_R |= shift;
               shift = shift<<1;
               GPIO_PORTE_DATA_R &= ~shift;
               col++;
               temp_key = GPIO_PORTB_DATA_R;
             }
             GPIO_PORTE_DATA_R |= shift;

        }
    else if((temp_key & 0x08) != 0)
        {
           row = 4;
           GPIO_PORTE_DATA_R &= ~0x02;
           temp_key = GPIO_PORTB_DATA_R;
             while(temp_key & 0x0F)
             {
               GPIO_PORTE_DATA_R |= shift;
               shift = shift<<1;
               GPIO_PORTE_DATA_R &= ~shift;
               col++;
               temp_key = GPIO_PORTB_DATA_R;
             }
             GPIO_PORTE_DATA_R |= shift;
        }
    switch(col + 3*(row-1))
    {
        case 1:return '1';
        case 2:return '2';
        case 3:return '3';
        case 4:return '4';
        case 5:return '5';
        case 6:return '6';
        case 7:return '7';
        case 8:return '8';
        case 9:return '9';
        case 10:return '*';
        case 11:return '0';
        case 12:return '#';
        default: return 0;
    }
}

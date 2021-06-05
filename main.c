#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include "GPS.h"

int pointer = 0;
double latitude,longitude,time=0;
double data_log[100][3];


void PortF_Init(void){
  SYSCTL_RCGC2_R |= 0x20;     						// 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R & 0x20) == 0){}; 	// allow time for clock to start
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   					// 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           						// allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;        						// 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   						// 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          						// 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        						// 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          						// 7) enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          						// 8) enable digital I/O on PF4-0
}

void UART2_Init(void){
  SYSCTL_RCGC1_R |= 0x04; 								// activate UART1
  SYSCTL_RCGC2_R |= 0x08; 							// activate port D
  while((SYSCTL_PRGPIO_R & 0x08) == 0){}; // allow time for clock to start
  UART2_CTL_R &= ~0x01;      							// disable UART
  UART2_IBRD_R = 104;                    // IBRD = int(16,000,000 / (16 * 9,600)) = int(104.1667)
  UART2_FBRD_R = 11;                     // FBRD = int(0.1667 * 64 + 0.5) = 11                  
  UART2_LCRH_R |=0x60;
  UART2_CTL_R |= 0x301;       					// enable UART
  GPIO_PORTD_AFSEL_R |= 0xC0;           // enable alt funct on PA1-0
  GPIO_PORTD_DEN_R |= 0xC0;             // enable digital I/O on PA1-0                            
  GPIO_PORTD_PCTL_R |= 0x11000000 ;			// configure PA1-1 as UART
  GPIO_PORTD_AMSEL_R &= ~0xC0;          // disable analog functionality on PA
}


int main(void){
    PortF_Init();
    UART2_Init();
    while(1){ //program loop
        gps_fetch(&latitude,&longitude,&time);
        data_log[pointer][0] = latitude;
        data_log[pointer][1] = longitude;
        data_log[pointer][2] = time;
        pointer++;
    }   //end program loop
}   //end main

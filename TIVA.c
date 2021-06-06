#include    "tm4c123gh6pm.h"

void PortA_Init(void){
  SYSCTL_RCGC2_R |= 0x01;                            // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R & 0x01) == 0){};              // allow time for clock to start
  GPIO_PORTA_CR_R = 0x0C;                                   // allow changes to PF4-0
  GPIO_PORTA_AMSEL_R = 0x00;                                // 3) disable analog on PF
  GPIO_PORTA_DIR_R = 0x0F;                                  // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTA_DEN_R = 0x0C;                                  // 8) enable digital I/O on PF4-0
}
void PortB_Init(void){
  SYSCTL_RCGC2_R |= 0x02;                            // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R & 0x02) == 0){};     // allow time for clock to start
  GPIO_PORTB_CR_R = 0xFF;                                   // allow changes to PF4-0
  GPIO_PORTB_AMSEL_R = 0x00;                                // 3) disable analog on PF
  GPIO_PORTB_PCTL_R = 0x00;                                 // 4) PCTL GPIO on PF4-0
  GPIO_PORTB_DIR_R = 0xFF;                                  // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTB_AFSEL_R = 0x00;                                // 6) disable alt funct on PF7-0
  GPIO_PORTB_PUR_R = 0x00;                                  // 7) enable pull-up on PF0 and PF4
  GPIO_PORTB_DEN_R = 0xFF;                                  // 8) enable digital I/O on PF4-0
}
void PortF_Init(void){
  SYSCTL_RCGC2_R |= 0x20;                           // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R & 0x20) == 0){};   // allow time for clock to start
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;                    // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;                                   // allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;                                // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;                           // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;                                  // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;                                // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;                                  // 7) enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;                                  // 8) enable digital I/O on PF4-0
  GPIO_PORTF_DATA_R &= ~0x0E;
}
void UART0_Init(void){
  SYSCTL_RCGC1_R |= 0x01;                // activate UART0
  SYSCTL_RCGC2_R |= 0x01;                // activate port A
  while((SYSCTL_PRGPIO_R & 0x01) == 0){};// allow time for clock to start
  UART0_CTL_R &= ~0x01;                  // disable UART
  UART0_IBRD_R = 104;                    // IBRD = int(16,000,000 / (16 * 9,600)) = int(104.1667)
  UART0_FBRD_R = 11;                     // FBRD = int(0.1667 * 64 + 0.5) = 11
  UART0_LCRH_R |=0x60;
  UART0_CTL_R |= 0x301;                 // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
  GPIO_PORTA_PCTL_R |= 0x11 ;           // configure PA1-1 as UART
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}
void UART2_Init(void){
  SYSCTL_RCGC1_R |= 0x04;                               // activate UART2
  SYSCTL_RCGC2_R |= 0x08;                           // activate port D
  while((SYSCTL_PRGPIO_R & 0x08) == 0){}; // allow time for clock to start
  UART2_CTL_R &= ~0x01;                                 // disable UART
  UART2_IBRD_R = 104;                    // IBRD = int(16,000,000 / (16 * 9,600)) = int(104.1667)
  UART2_FBRD_R = 11;                     // FBRD = int(0.1667 * 64 + 0.5) = 11
  UART2_LCRH_R |=0x60;
  UART2_CTL_R |= 0x301;                         // enable UART
  GPIO_PORTD_AFSEL_R |= 0xC0;           // enable alt funct on PA1-0
  GPIO_PORTD_DEN_R |= 0xC0;             // enable digital I/O on PA1-0
  GPIO_PORTD_PCTL_R |= 0x11000000 ;         // configure PA1-1 as UART
  GPIO_PORTD_AMSEL_R &= ~0xC0;          // disable analog functionality on PA
}
void Red_LED(char on){
    if(on)  GPIO_PORTF_DATA_R |= 0x02;
    else    GPIO_PORTF_DATA_R &= ~0x02;
}

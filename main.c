#include "tm4c123gh6pm.h"

unsigned long Led;

void PortF_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;     						// 1) activate clock for Port F
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
  SYSCTL_RCGCGPIO_R |= 0x08; 							// activate port D
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
void UART0_Init(void){
	SYSCTL_RCGC1_R |= 0x01; 								// activate UART1
  SYSCTL_RCGCGPIO_R |= 0x01; 							// activate port D
	while((SYSCTL_PRGPIO_R & 0x01) == 0){}; // allow time for clock to start
  UART0_CTL_R &= ~0x01;      							// disable UART
  UART0_IBRD_R = 104;                    // IBRD = int(16,000,000 / (16 * 9,600)) = int(104.1667)
  UART0_FBRD_R = 11;                     // FBRD = int(0.1667 * 64 + 0.5) = 11                  
	UART0_LCRH_R |=0x60;
  UART0_CTL_R |= 0x301;       					// enable UART
	GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0                            
  GPIO_PORTA_PCTL_R |= 0x11 ;			// configure PA1-1 as UART
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}


void UART_Init0(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART2
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 104;//27;                    // IBRD = int(16,000,000 / (16 * 9600)) = int(27.1267)
  UART0_FBRD_R = 11;//8;                     // FBRD = int(0.1267 * 64 + 0.5) = 8
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}

void Delay(void){unsigned long volatile time;
  time = 145448;  // 0.1sec
  while(time){
		time--;
  }
}

int main(void){  
  PortF_Init();  // make PF1 out (PF1 built-in LED)
	UART2_Init();
	UART_Init0();
	/*
	Led = GPIO_PORTF_DATA_R;   
	Led |= 0x08;
	GPIO_PORTF_DATA_R = Led;
  */
	while(1){
		unsigned long volatile data;
		while((UART2_FR_R & 0x10) != 0){};
		data = UART2_DR_R;
			
		while((UART0_FR_R&UART_FR_TXFF) != 0);
		UART0_DR_R = UART2_DR_R;
  }
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

#include    "tm4c123gh6pm.h"
#include    "TIVA.h"
#include    "LCD.h"
#include    "math.h"

void Initialize(void){
    PortA_Init();
    PortB_Init();
    PortF_Init();
    UART0_Init();
    UART2_Init();
    lcd_init();
    display_2d("Please Wait","Initializing.");
    Delay(1008960);    //wait 1 seconds
    lcd_set_cursor(0,0);
    display_2d("Please Wait","Initializing..");
    Delay(1008960);    //wait 1 seconds
    lcd_set_cursor(0,0);
    display_2d("Please Wait","Initializing...");
    Delay(1008960);    //wait 1 seconds
}
void Delay(long time){
  while(time) time--;
}

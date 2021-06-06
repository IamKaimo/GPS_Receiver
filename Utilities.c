#include    "tm4c123gh6pm.h"
#include    "TIVA.h"
#include    "LCD.h"
#include    "math.h"
#define PI 3.14159265


void Delay(long time){
  while(time) time--;
}
void Initialize(void){
    PortA_Init();
    PortB_Init();
    PortF_Init();
    UART0_Init();
    UART2_Init();
    lcd_init();
}
double calc_distance(double new_lat,double new_lon,double old_lat,double old_lon){
    float R = 6371000;
    float o1 = old_lat * PI/180;
    float o2 = new_lat * PI/180;
    float delta_o = o2-o1;
    float delta_l = (new_lon - old_lon) * PI/180;
    float a = sin(delta_o/2) * sin(delta_o/2) + cos(o1) * cos(o2) * sin(delta_l/2) * sin(delta_l/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    float d = R * c; // in meters
    return d;
}
void dec_to_dms(double dec,double* arr){
    arr[1]= dec - (int)dec;
    arr[0]= dec - arr[1];
    arr[1] = arr[1] * 60;
    arr[2] = arr[1] - (int)arr[1];
    arr[1] = arr[1] - arr[2];
    arr[2]= arr[2] * 60;
}
void check_distance(double total_distance){
    if(total_distance >= 100) Red_LED(1);
    else    Red_LED(0);
}

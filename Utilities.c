#include    "tm4c123gh6pm.h"
#include    "TIVA.h"
#include    "LCD.h"
#include    "math.h"
#define PI 3.14159265


void Delay(long time){
  while(time) time--;
}
void display_2d(char* data1,char* data2){
    lcd_set_cursor(0,0);        //cursor at first line
    display_data(data1);  //out the data
    lcd_set_cursor(1,0);        //cursor at second line
    display_data(data2);    //out the data
}
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
void int_to_str(int num,char* str){
    int digits = 0,fake = num,i;
    double fake2 = num;
    if(num ==0)digits = 1;
    else{
        while(fake){
            fake = fake/10;
            digits++;
        }
    }
    fake2= fake2/pow(10,digits);
    for(i=0;i<digits;i++){
        fake2 = fake2*10;
        str[i] = (int)fake2 + 48;
        fake2 = fake2 - (int)fake2;
    }
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

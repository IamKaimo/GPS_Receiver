#ifndef UTILITIES_H
#define UTILITIES_H
void Initialize(void);
void Delay(long time);
void display_2d(char* data1,char* data2);
double calc_distance(double new_lat,double new_lon,double old_lat,double old_lon);
void int_to_str(int num,char* str);
void dec_to_dms(double dec,double* arr);
void check_distance(double total_distance,int target_distance);
#endif

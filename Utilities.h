#ifndef UTILITIES_H
#define UTILITIES_H
void Initialize(void);
void Delay(long time);
double calc_distance(double new_lat,double new_lon,double old_lat,double old_lon);
void dec_to_dms(double dec,double* arr);
void check_distance(double total_distance);
#endif

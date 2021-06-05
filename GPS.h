#ifndef GPS_H_
#define GPS_H_

char gps_fetch(double* new_lat,double* new_lon,double* new_time);
void dec_to_dms(double dec,double* arr);

#endif /* GPS_H_ */

#ifndef GPS_H
#define GPS_H

#include "headfile.h"
extern double gps_X;
extern double gps_Y;
extern double gps_X0;
extern double gps_Y0;
void ErrorLog(int num);
void ParseGpsBuffer(void);
double Convert_to_degrees(char* data);
void PrintGpsBuffer(void);
int LongLat2XY(double longitude,double latitude,double *X,double *Y);



#endif
#ifndef GPS_H
#define GPS_H

#include "headfile.h"

void ErrorLog(int num);
void ParseGpsBuffer(void);
double Convert_to_degrees(char* data);
void PrintGpsBuffer(void);
void LongLat2XY(double longitude,double latitude,double *X,double *Y);



#endif
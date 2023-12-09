//IST.c
//2023.11.3
//by gjx

#include "IST.h"

float IST8310data[3];

void IST_read()
{
	ist8310_read_mag(IST8310data);
}

void IST_print()
{
	usart_printf("X=%d,Y=%d,Z=%d\r\n",(int)(IST8310data[0]*10),(int)(IST8310data[1]*10),(int)(IST8310data[2]*10));
}	

void IST_Vofa_print()
{
	usart_printf("%d,%d,%d\n",(int)(IST8310data[0]*10),(int)(IST8310data[1]*10),(int)(IST8310data[2]*10));
}	
		
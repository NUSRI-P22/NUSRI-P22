#include "gps.h"



void ErrorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}
void ParseGpsBuffer(void)
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		printf("**************\r\n");
		printf("%s",Save_Data.GPS_Buffer);
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					ErrorLog(1);	//½⎶´펳
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//»񈡕TCʱ¼䊉					case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//»񈡕TCʱ¼䊉					case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//»񈡎³¶Ȑŏ¢
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//»񈡎/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//»񈡾­¶Ȑŏ¢
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//»񈡅/W

						default:break;
					}
					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;
				}
				else
				{
					ErrorLog(2);	//½⎶´펳
				}
			}
		}
	}
	LongLat2XY(Convert_to_degrees(Save_Data.longitude),Convert_to_degrees(Save_Data.latitude),&Save_Data.X,&Save_Data.Y);
}

// GPSʽ¾ݗª»¯µ¥λΪ¶ȡ£
double Convert_to_degrees(char* data)
{
	double temp_data = atof(data);
	int degree = (int)(temp_data / 100);
	double f_degree = (temp_data / 100.0 - degree)*100/60.0;
	double result = degree + f_degree;
	return result;
}


void PrintGpsBuffer(void)
{
	double f_latitude = 0.0;
	double f_longitude = 0.0;
	
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		
		printf("Save_Data.UTCTime = ");
		//printf(Save_Data.UTCTime);
		printf("%s",Save_Data.UTCTime);
		printf("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			printf("Save_Data.latitude = ");
			// printf(Save_Data.latitude);
			// printf("--");
			f_latitude = Convert_to_degrees(Save_Data.latitude);
			printf("%lf%s", f_latitude, Save_Data.N_S);
			printf("\r\n");

			printf("Save_Data.N_S = ");
			//printf(Save_Data.N_S);
			printf("%s",Save_Data.N_S);
			printf("\r\n");

			printf("Save_Data.longitude = ");
			// printf(Save_Data.longitude);
			// printf("--");
			f_longitude = Convert_to_degrees(Save_Data.longitude);
			printf("%lf%s", f_longitude, Save_Data.E_W);
			printf("\r\n");

			printf("Save_Data.E_W = ");
			//printf(Save_Data.E_W);
			printf("%s",Save_Data.E_W);
			printf("\r\n");
		}
		else
		{
			printf("GPS DATA is not usefull!\r\n");
		}
		
	}
}



//¾­γ¶ȗø±ꏵת»»Ϊµѿ¨¶û׸±ꏵˣ·¨ 
void LongLat2XY(double longitude,double latitude,double *X,double *Y)
{
			int ProjNo=0; int ZoneWide; 
			double longitude1,latitude1, longitude0,latitude0, X0,Y0, xval,yval;
			double a,f, e2,ee, NN, T,C,A, M, iPI;
			iPI = 0.0174532925199433; //3.1415926535898/180.0;
			ZoneWide = 3;//3¶ȴø¿튉		//ZoneWide = 6; 6¶ȴø¿𒠉		//a=6378245.0; f=1.0/298.3; //54Ī±±¾©׸±ꏵ²Ίý 
			a=6378140.0; f=1/298.257; //80Īη°²׸±ꏵ²Ίý 
			a = 6378137.0; f = 1.0/298.257223563;//WGS84׸±ꏵ²Ίý
			//ProjNo = (int)(longitude / ZoneWide) ;      //6¶ȴø
			//longitude0 = ProjNo * ZoneWide + ZoneWide / 2; //6¶ȴø
			ProjNo = (int)(longitude / ZoneWide+0.5) ; 
					 // ProjNo = (int)(longitude / ZoneWide) ; //--´øºŊ			longitude0 = ProjNo * ZoneWide ; //--֐ѫדΧϟ
			longitude0 = longitude0 * iPI ;//--֐ѫדΧϟת»¯δ»¡¶Ȋ			latitude0=0; 
			longitude1 = longitude * iPI ; //¾­¶ȗª»»Ϊ»¡¶Ȋ			latitude1 = latitude * iPI ; //γ¶ȗª»»Ϊ»¡¶Ȋ			e2=2*f-f*f;
			ee=e2*(1.0-e2);
			NN=a/sqrt(1.0-e2*sin(latitude1)*sin(latitude1));
			T=tan(latitude1)*tan(latitude1);
			C=ee*cos(latitude1)*cos(latitude1);
			A=(longitude1-longitude0)*cos(latitude1); 	

			M=a*((1-e2/4-3*e2*e2/64-5*e2*e2*e2/256)*latitude1-(3*e2/8+3*e2*e2/32+45*e2*e2
				*e2/1024)*sin(2*latitude1)
				+(15*e2*e2/256+45*e2*e2*e2/1024)*sin(4*latitude1)-(35*e2*e2*e2/3072)*sin(6*latitude1));
			xval = NN*(A+(1-T+C)*A*A*A/6+(5-18*T+T*T+72*C-58*ee)*A*A*A*A*A/120);
			yval = M+NN*tan(latitude1)*(A*A/2+(5-T+9*C+4*C*C)*A*A*A*A/24
				+(61-58*T+T*T+600*C-330*ee)*A*A*A*A*A*A/720);
			//X0 = 1000000L*(ProjNo+1)+500000L; //6¶ȴø
			X0 = 1000000L*ProjNo+500000L;  //3¶ȴø
			Y0 = 0; 
			xval = xval+X0; 
			yval = yval+Y0; 
			*X= xval;
			*Y= yval;
}





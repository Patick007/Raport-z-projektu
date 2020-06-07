#include <math.h>
#include <stdio.h>
#include "winbgi2.h"
#include <stdlib.h>
#include "rk4.h"
#define g 9.81
#define p 1.2
#define c 0.55
#define pi 4*atan(1.)
void funkcja(double t, double *X, double *Fx);
double r,m,a,s;
void main()
{
	FILE *f;
	FILE *l;
	f=fopen("wynikix.txt","w");
	l=fopen("wynikiy.txt","w");
	//warunki pocz¹tkowe
	double vx0;
	double vy0 = 0;
	double x0 = 0;
	double y0;
	double t = 0;

	double h = 0.002;
	double Fx[4];
	double X1[4];

	printf("promien kuli[cm]:\n"); //promien musi byc dodatni
	scanf("%lf", &r);
	printf("masa kuli[kg]:\n"); //masa musi byc nieujemna
	scanf("%lf", &m);
	s = pi*pow(0.01*r,2.);
	printf("wartosc wspolczynnika wiatru a [kg/s^2];\n");
	scanf("%lf", &a);
	printf("predkosc v0[m/s^2]:\n");
	scanf("%lf", &vx0);
	printf("wysokosc y0:\n"); //wysokosc musi byc nieujemna
	scanf("%lf", &y0);
	double X[4] = {x0, vx0, y0, vy0};
	

	graphics(900, 900);
	title("wykres x(t)","","");
	scale(0,-50,50,50);
	setcolor(1.0);
	while(t>=0)
	{
		fprintf(f,"%.3lf\t",t);
		fprintf(l,"%.3lf\t",t);
		vrk4(t,X,h,4,funkcja,X1);
		if(X1[2]<=0)
		{
			fprintf(f, "vx = 0.00\t\t x = %lf\n", X1[0]);
			fprintf(l, "vy = 0.00\t\t y = %lf\n", X1[2]);
			break;
		}
		fprintf(f,"vx = %lf\t\t x = %lf\n", X1[1],X1[0]);
		fprintf(l,"vy = %lf\t\t y = %lf\n", X1[3], X1[2]);
		circle(t,X1[0],3);
		X[0] = X1[0];
		X[1] = X1[1];
		X[2] = X1[2];
		X[3] = X1[3];
		t=t+h;
	}
/*	t=0;
	

	
	graphics(900,900);
	title("wykres y(t)","","");
	scale(0,-50,50,50);
	setcolor(1.0);
	while(t>=0)
	{
		vrk4(t,X,h,4,funkcja,X1);
		if(X1[2]<=0)
		{
			break;
		}
		circle(t,X1[2],3);
		X[0] = X1[0];
		X[1] = X1[1];
		X[2] = X1[2];
		X[3] = X1[3];
		t=t+h;
	}

	
	t=0;
	
	graphics(900,900);
	title("wykres vx(t)","","");
	scale(0,-50,50,50);
	setcolor(1.0);
	while(t>=0)
	{
		vrk4(t,X,h,4,funkcja,X1);
		if(X1[2]<=0)
		{
			break;
		}
		circle(t,X1[1],3);
		X[0] = X1[0];
		X[1] = X1[1];
		X[2] = X1[2];
		X[3] = X1[3];
		t=t+h;
	}
	
	t=0;
	
	graphics(900,900);
	title("wykres vy(t)","","");
	scale(0,-50,50,50);
	setcolor(1.0);
	while(t>=0)
	{
		vrk4(t,X,h,4,funkcja,X1);
		if(X1[2]<=0)
		{
			break;
		}
		circle(t,X1[3],3);
		X[0] = X1[0];
		X[1] = X1[1];
		X[2] = X1[2];
		X[3] = X1[3];
		t=t+h;
	}
*/
	fclose(f);
	fclose(l);
	
	wait();
	
}


void funkcja(double t, double *X, double *Fx)
{
	Fx[3] = s*c*pow(X[3],2)*p/(2*m) - g;
	Fx[2] = X[3];
	if(X[1]>=0)
	{
		Fx[1] = -a*X[2]/m - pow(X[1],2)*s*c*p/(2*m);
	} else if(X[1]<0)
	{
		Fx[1] = -a*X[2]/m + pow(X[1],2)*s*c*p/(2*m);
	}
	Fx[0] = X[1];

}
// StatCalc.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "RAWData.h"

int main(int argc, char *argv[])
{
	double x, y;
	x = 5.0;
	y = gsl_sf_bessel_J0(x);
	printf("J0(%g) = %.18e\n", x, y);
	system("pause");
	return 0;
}


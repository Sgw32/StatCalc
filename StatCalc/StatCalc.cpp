// StatCalc.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int main(void)
{
	double x, y;
	x = 5.0;
	y = gsl_sf_bessel_J0(x);
	printf("J0(%g) = %.18e\n", x, y);
	return 0;
}


// StatCalc.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "FileLoader.h"
#include "RegressionCalc.h"

int main(int argc, char *argv[])
{
	//double x, y;
	//x = 5.0;
	//y = gsl_sf_bessel_J0(x);
	//printf("J0(%g) = %.18e\n", x, y);

	FileLoader* fl = new FileLoader;
	fl->parseCommandLine(argc, argv);
	fl->loadData();
	RAWData* rda = fl->getRAWData();
	RegressionCalc rclc;
	rclc.loadRAWData(rda);
	rclc.calculateAscentPolynomial(0, rda->getEndOfAscent(), 5);
	rclc.calculateAscentPolynomial(0, rda->getEndOfAscent(), 4);
	rclc.calculateAscentPolynomial(0, rda->getEndOfAscent(), 3);
	rclc.calculateAscentPolynomial(0, rda->getEndOfAscent(), 2);
	system("pause");
	return 0;
}


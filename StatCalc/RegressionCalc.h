#include "stdafx.h"
#include "RAWData.h"

#ifndef REGRESSIONCALC_H
#define REGRESSIONCALC_H

class RegressionCalc
{
public:
	RegressionCalc();
	~RegressionCalc();
	void loadRAWData(RAWData* rawdata);
	void calculateAscentPolynomial();
	void calculateAscentPolynomial(int tstart, int tend); //Пятый порядок
	void calculateAscentPolynomial(int tstart, int tend, int order);
	
	vector<double> returnPolynomial();
	void copyGSLPolynomial();
	gsl_vector* returnGSLPolynomial();
private:
	RAWData* rDa;
	gsl_matrix *X, *cov;
	gsl_vector *y, *w, *c;
	gsl_vector *c_poly;
};

#endif
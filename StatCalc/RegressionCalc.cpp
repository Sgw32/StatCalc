#include "stdafx.h"
#include "RegressionCalc.h"

RegressionCalc::RegressionCalc()
{
	c_poly = 0;
}

RegressionCalc::~RegressionCalc()
{

}

void RegressionCalc::loadRAWData(RAWData* rawdata)
{
	rDa = rawdata;
}

void RegressionCalc::calculateAscentPolynomial()
{

}

void RegressionCalc::calculateAscentPolynomial(int tstart, int tend)
{
	map<int, float>::iterator ist;
	map<int, float>::iterator ien;

	ist = rDa->getIteratorByTimePoint(tstart);
	ien = rDa->getIteratorByTimePoint(tend);

	int n;
	double xi, yi, ei, chisq;
	gsl_matrix *X, *cov;
	gsl_vector *y, *w, *c;
	n = std::distance(ist,ien); //Длина выборки
	X = gsl_matrix_alloc(n, 5);
	y = gsl_vector_alloc(n);
	w = gsl_vector_alloc(n);

	c = gsl_vector_alloc(5);
	cov = gsl_matrix_alloc(5, 5);

	map<int, float>::iterator i;

	int it1 = 0;
	for (i = ist; i != ien; i++)
	{
		/*int count = fscanf(stdin, "%lg %lg %lg",
			&xi, &yi, &ei);

		if (count != 3)
		{
			fprintf(stderr, "error reading file\n");
			exit(-1);
		}

		printf("%g %g +/- %g\n", xi, yi, ei);
		*/
		xi = (*i).first;
		yi = (*i).second;
		ei = 0;

		gsl_matrix_set(X, it1, 0, 1.0);
		gsl_matrix_set(X, it1, 1, xi);
		gsl_matrix_set(X, it1, 2, xi*xi);
		gsl_matrix_set(X, it1, 3, xi*xi*xi);
		gsl_matrix_set(X, it1, 4, xi*xi*xi*xi);

		gsl_vector_set(y, it1, yi);
		gsl_vector_set(w, it1, 1.0 / (ei*ei));
		it1++;
	}

	{
		gsl_multifit_linear_workspace * work
			= gsl_multifit_linear_alloc(n, 5);
		gsl_multifit_linear(X, y, c, cov,
			&chisq, work);
		gsl_multifit_linear_free(work);
	}

#define C(i) (gsl_vector_get(c,(i)))
#define COV(i,j) (gsl_matrix_get(cov,(i),(j)))

	{
		printf("# best fit: Y = %g + %g X + %g X^2 + %g X^3 + %g X^4\n",
			C(0), C(1), C(2), C(3), C(4));
	}


	gsl_matrix_free(X);
	gsl_vector_free(y);
	gsl_vector_free(w);
	gsl_vector_free(c);
	gsl_matrix_free(cov);
}

void RegressionCalc::calculateAscentPolynomial(int tstart, int tend, int order)
{
	if ((order<2) || (order>5))
		return;
	map<int, float>::iterator ist;
	map<int, float>::iterator ien;

	ist = rDa->getIteratorByPoint(tstart);
	ien = rDa->getIteratorByPoint(tend);

	int n;
	double xi, yi, ei, chisq;

	n = std::distance(ist, ien); //Длина выборки
	X = gsl_matrix_alloc(n, order);
	y = gsl_vector_alloc(n);
	w = gsl_vector_alloc(n);

	c = gsl_vector_alloc(order);
	cov = gsl_matrix_alloc(order, order);

	map<int, float>::iterator i;

	int it1 = 0;
	for (i = ist; i != ien; i++)
	{
		/*int count = fscanf(stdin, "%lg %lg %lg",
		&xi, &yi, &ei);

		if (count != 3)
		{
		fprintf(stderr, "error reading file\n");
		exit(-1);
		}

		printf("%g %g +/- %g\n", xi, yi, ei);
		*/
		xi = (*i).first;
		yi = (*i).second;
		ei = 0;

		for (int j = 0; j != order;j++)
		gsl_matrix_set(X, it1, j, pow(xi,(double)j));

		gsl_vector_set(y, it1, yi);
		it1++;
	}

	{
		gsl_multifit_linear_workspace * work
			= gsl_multifit_linear_alloc(n, order);
		gsl_multifit_linear(X, y, c, cov,
			&chisq, work);
		gsl_multifit_linear_free(work);
	}

#define C(i) (gsl_vector_get(c,(i)))
#define COV(i,j) (gsl_matrix_get(cov,(i),(j)))


	switch (order)
	{
	case 5:
		printf("# best fit: Y = %g + %g X + %g X^2 + %g X^3 + %g X^4\n",
			C(0), C(1), C(2), C(3), C(4));
		break;
	case 4:
		printf("# best fit: Y = %g + %g X + %g X^2 + %g X^3\n",
			C(0), C(1), C(2), C(3));
		break;
	case 3:
		printf("# best fit: Y = %g + %g X + %g X^2\n",
			C(0), C(1), C(2));
		break;
	case 2:
		printf("# best fit: Y = %g + %g X\n",
			C(0), C(1));
		break;
	default:
		break;
	}
	copyGSLPolynomial();
	gsl_matrix_free(X);
	gsl_vector_free(y);
	gsl_vector_free(w);
	gsl_vector_free(c);
	gsl_matrix_free(cov);
}

void RegressionCalc::copyGSLPolynomial()
{
	if (c_poly)
		gsl_vector_free(c_poly);
	c_poly = gsl_vector_alloc(c->size);
	gsl_vector_memcpy(c_poly, c);
}

gsl_vector* RegressionCalc::returnGSLPolynomial()
{
	return c_poly;
}

vector<double> RegressionCalc::returnPolynomial()
{
	vector<double> res;
	return res;
}
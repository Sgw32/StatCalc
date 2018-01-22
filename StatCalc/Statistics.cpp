#include "stdafx.h"
#include "Statistics.h"

Statistics::Statistics()
{

}

Statistics::~Statistics()
{

}

void Statistics::loadRAWData(RAWData* rawdata)
{
	rDa = rawdata;
}

void Statistics::loadRegressionCalc(RegressionCalc* rclc)
{
	rcalc = rclc;
}

void Statistics::loadLayers(pair<map<int, float>, map<int, float>> layers)
{
	mLayers = layers;
}

void Statistics::makeWorkLayers()
{
	makeMainWorkLayer();
	//��� ����� ��������� �������� �� ������ � ����� ����.
	timeHLayersStart = mLayers.first;
	timeHLayersEnd = mLayers.second;

	map<int, float>::iterator it_s;
	map<int, float>::iterator it_e = timeHLayersEnd.begin();
	//�������� �� ���� �����.
	for (it_s = timeHLayersStart.begin(); it_s != timeHLayersStart.end(); it_s++)
	{
		WorkLayer* wly = new WorkLayer();
		//������ � ����� ���� � �������� �� ������ ������
		int st_i = rDa->getPointByIterator(it_s);
		int en_i = rDa->getPointByIterator(it_e);

		//����������� ������� ��� ����� ����.
		rcalc->calculateAscentPolynomial(st_i, en_i, 5); 
		gsl_vector* c_poly_5 = rcalc->returnGSLPolynomial();
		
		for (int i = st_i; i != en_i;i++)
		{
			map<int, float>::iterator it = rDa->getIteratorByPoint(i);
			//� ������ ������� ���� ��������� ������� �������� � �������� ������ �� ����
			float val = gsl_poly_eval(c_poly_5->data, c_poly_5->size, (*it).first);
			wly->addData((*it).first, val-(*it).second);
		}
		workLayers.push_back(wly);
		it_e++;
	}
}

void Statistics::makeMainWorkLayer()
{
	WorkLayer* wly = new WorkLayer();
	//�������� ����� ������� 4 ������� ��� ����� �����(�� �������)
	rcalc->calculateAscentPolynomial(0, rDa->getEndOfAscentPoint(), 5);
	gsl_vector* c_poly_5 = rcalc->returnGSLPolynomial();
	map<int, float>::iterator it;
	for (it = rDa->H.begin(); it != rDa->H.end(); it++)
	{
		float val = gsl_poly_eval(c_poly_5->data, c_poly_5->size, (*it).first);
		wly->addData((*it).first, val - (*it).second);
	}
}

void Statistics::computeStatistics()
{

}
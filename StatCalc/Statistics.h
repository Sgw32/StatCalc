#include "stdafx.h"
#include "RAWData.h"
#include "RegressionCalc.h"

#ifndef STATISTICS_H
#define STATISTICS_H

/*

������� ���� ��������� �� ���� ��� ������ �� RAW �� ����.
����� ��������� ������� � ���.

*/

class WorkLayer
{
public:
	WorkLayer(){};
	~WorkLayer();
	void addData(int x, float y)
	{
		mData[x] = y;
	}
	float medium()
	{
		float res = 0;
		map<int, float>::iterator it;
		for (it = mData.begin(); it != mData.end(); it++)
		{
			res += (*it).second;
		}
		return res;
	}
	float computeStDev()
	{
		map<int, float>::iterator it;
		float m = medium();
		float res = 0;
		for (it = mData.begin(); it != mData.end(); it++)
		{
			res += ((*it).second - m)*((*it).second - m);
		}
		res /= mData.size();
		res = sqrt(res);
		return res;
	}
	map<int, float> mData;
};

class Statistics
{
public:
	Statistics();
	~Statistics();
	//�������� ������
	void loadRAWData(RAWData* rawdata);
	void loadRegressionCalc(RegressionCalc* rclc);
	void loadLayers(pair<map<int, float>, map<int, float>> layers);
	//�������� ������� ����
	void makeWorkLayers();
	//���������� ����������
	void computeStatistics();
private:
	void makeMainWorkLayer();
	pair<map<int, float>, map<int, float>> mLayers;
	map<int, float> timeHLayersStart;
	map<int, float> timeHLayersEnd;
	WorkLayer* mainWorkLayer;
	vector<WorkLayer*> workLayers;
	RAWData* rDa;
	RegressionCalc* rcalc;
};

#endif
#include "stdafx.h"
#include "RAWData.h"
#include "RegressionCalc.h"
#include "WorkLayer.h"

#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics
{
public:
	Statistics();
	~Statistics();
	//�������� ������
	void loadRAWData(RAWData* rawdata);
	void loadRegressionCalc(RegressionCalc* rclc);
	void loadLayers(pair<map<int, float>, map<int, float>> layers);
	void load5000Layers(vector<int> m500l);
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
	vector<int> m5000Layers;
	vector<WorkLayer*> workLayers;
	vector<pair<float, float>> errors;
	RAWData* rDa;
	RegressionCalc* rcalc;
};

#endif
#include "stdafx.h"
#include "minicsv.h"
#include "WorkLayer.h"
#include "RAWData.h"

using namespace mini;

#ifndef REPORTWRITER_H
#define REPORTWRITER_H

class ResultPair
{
public:
	ResultPair(){}
	~ResultPair();
	int point;
	int time;
	float dev;
	float errors2;
	float errors3;
};

class ReportWriter
{
public:
	static ReportWriter& Instance()
	{
		// �������� ���������, ���� ��� ������� � ����������������
		static ReportWriter s;
		return s;
	}
	void init();
	void addResultPair(int point, int time, float dev, float errors2, float errors3);
	void setWorkLayers(vector<WorkLayer*> wlayers);
	void setRAWData(RAWData* rda);
	void writeReport(string filename);
private:
	void writeResults(int count, csv::ofstream& os);
	void writeWorkLayers(int count, csv::ofstream& os);
	RAWData* rDa;
	vector<ResultPair*> resPairs;
	vector<WorkLayer*> workLayers;
	ReportWriter() 
	{
	}  // ����������� ����������
	~ReportWriter() 
	{
	} // � ����������

	// ���������� ����� ��������� �����������
	ReportWriter(ReportWriter const&); // ���������� �� �����
	ReportWriter& operator= (ReportWriter const&);  // � ���
};

#endif
#include "stdafx.h"
#include "ReportWriter.h"

void ReportWriter::init()
{

}

void ReportWriter::addResultPair(int point, int time, float dev, float errors2, float errors3)
{
	ResultPair* rp = new ResultPair;
	rp->dev = dev;
	rp->errors2 = errors2;
	rp->errors3 = errors3;
	rp->point = point;
	rp->time = time;
	resPairs.push_back(rp);
}

void ReportWriter::setWorkLayers(vector<WorkLayer*> wlayers)
{
	workLayers = wlayers;
}

void ReportWriter::setRAWData(RAWData* rda)
{
	rDa = rda;
}

void ReportWriter::writeWorkLayers(int count, csv::ofstream& os)
{
	vector<WorkLayer*>::iterator it;
	for (it = workLayers.begin(); it != workLayers.end(); it++)
	{
		WorkLayer* wly = (*it);
		map<int, float>::iterator di = wly->mData.begin();
		advance(di, count);
		os << (*di).second;
	}
}

void ReportWriter::writeResults(int count, csv::ofstream& os)
{
	int c2 = (count > (resPairs.size()-1)) ? (-1) : count;
	if (c2 > -1)
	{
		vector<ResultPair*>::iterator it = resPairs.begin();
		advance(it, c2);
		ResultPair* rp = (*it);
		os << rp->point+1 << rp->time << rp->dev << rp->errors2 << rp->errors3;
	}
	else
	{
		os << "" << "" << "" << "" << "";
	}
	
}

void ReportWriter::writeReport(string filename)
{
	csv::ofstream os(filename);
	os.set_delimiter(';', "$$");
	if (os.is_open())
	{
		os << "RAWDataT" << "RAWDataH" << "LAYERS";
		vector<WorkLayer*>::iterator it;
		for (it = workLayers.begin(); it != workLayers.end()-1; it++)
		{
			os << "";
		}
		os << "RESULTS" << NEWLINE;

		int count = rDa->getEndOfAscentPoint();
		for (int i = 0; i != count; i++)
		{
			os << (*rDa->getIteratorByPoint(i)).first;
			os << (*rDa->getIteratorByPoint(i)).second;
			writeWorkLayers(i, os);
			writeResults(i, os);
			os << NEWLINE;
		}
		
	}
	os.flush();
}
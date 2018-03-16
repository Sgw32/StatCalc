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
	size_t ps = rcalc->polynomials.size();
	int c2 = (count > (resPairs.size()-1)) ? (-1) : count;
	int c3 = (count > (resPairs.size() + 1 + ps - 1)) ? (-1) : count - resPairs.size();
	if (c2 > -1)
	{
		vector<ResultPair*>::iterator it = resPairs.begin();
		advance(it, c2);
		ResultPair* rp = (*it);
		os << rp->point+1 << rp->time << rp->dev << rp->errors2 << rp->errors3;
	}
	else if (c3 > -1)
	{
		if (!c3)
		{
			os << "POLYNOMIALS" << "" << "" << "" << "";
		}
		else
		{
			os << rcalc->polynomials[c3-1];
		}
	}
	else
	{
		os << "" << "" << "" << "" << "";
	}
	
}

void ReportWriter::loadRegressionCalc(RegressionCalc* rclc)
{
	rcalc = rclc;
}

void ReportWriter::writeReport(string filename)
{
	csv::ofstream os(filename);
	os.set_delimiter(';', "$$");
	if (os.is_open())
	{
		os << "RAWDataT" << "RAWDataH";
		vector<WorkLayer*>::iterator it;
		int cnt = 0;
		for (it = workLayers.begin(); it != workLayers.end(); it++)
		{
			stringstream ss;
			ss << "LAYER" << cnt;
			os << ss.str();
			ss.flush();
			cnt++;
		}
		os << "LS" << "LE" << "DEV" << "ES2" << "ES3" << NEWLINE;

		int count = rDa->getEndOfAscentPoint();
		for (int i = 0; i != count; i++)
		{
			os << (*rDa->getIteratorByPoint(i)).first; //RAW Data
			os << (*rDa->getIteratorByPoint(i)).second; //RAW Data
			writeWorkLayers(i, os); //Polynomials
			writeResults(i, os);//Results table
			os << NEWLINE;
		}
		
	}
	os.flush();
}
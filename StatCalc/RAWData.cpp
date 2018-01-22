#include "stdafx.h"
#include "RAWData.h"

RAWData::RAWData()
{
	maxAltitude = 0;
	maxDistance = 0;
	alt10Elevation = -1;
	minElevation = -1;
	endOfAscent = 0;
	endOfAscentPoint = 0;
}

float RAWData::getMinTemperature()
{
	float t = T[0];
	for (int i = 1; i != T.size(); i++)
	{
		if (T[i] < t)
			t = T[i];
	}
	return t;
}

float RAWData::getMinTemperature(float Hthr)
{
	int cnt = 0;
	for (int i = 1; i != T.size(); i++)
	{
		if (H[i] > Hthr)
			cnt = i;
	}
	float t = T[cnt];
	for (int i = cnt; i != T.size(); i++)
	{
		if (T[i] < t)
			t = T[i];
	}
	return t;
}

float RAWData::getGroundTemperature()
{
	float t = 0;
	

	if ((T.size() < 100) && (T.size() > 0))
	{
		t = (*T.begin()).second;
		return t;
	}
		
	if (T.size() == 0)
		return -1;
	int time = 0;
	//for (int i = 0; i != 60; i++)
	//OLD
	/*i2 = T.begin();
	i2++;
	i2++;
	i2++;
	i2++;
	i2++;
	i2++;
	for (i = T.begin(); i != i2; i++)
	{
	t += (*i).second;
	}
	t /= 6;*/
	map<int, float>::iterator i, j;
	i = j = T.begin();

	i++;
	while ((*i).first < 50)
	{
		for (time = (*j).first; time != (*i).first; time++)
		{
			float curdata = ((*i).second - (*j).second) / ((*i).first - (*j).first) * (time - (*j).first) + (*j).second;
			t += curdata;
			//cout << curdata << endl;
		}
		j++;
		i++;
	}
	for (time = (*j).first; time != 50; time++)
	{
		float curdata = ((*i).second - (*j).second) / ((*i).first - (*j).first) * (time - (*j).first) + (*j).second;
		t += curdata;
		//cout << curdata << endl;
	}
	//t += ((*i).second - (*j).second) / ((*i).first - (*j).first) * (25 - (*j).first) + (*j).second; //Finish to 60 sec
	t /= (50 - (*T.begin()).first);
	return t;
}

int RAWData::getSoundingTime()
{
	if (H.size() == 0)
		return 0;
	map<int, float>::iterator it = H.end();
	it--;
	return (*it).first;
}

void RAWData::addString(string str)
{
	int time;
	float mH, mD, mE, mA, mT, mU;
	string arr[7];
	//sscanf_s(str.c_str(), "%d %f %f %f %f %f %f", &time, &mH, &mD, &mE, &mA, &ssT, &ssU);
	stringstream ssin(str);
	int i = 0;
	while (ssin.good() && i < 7){
		ssin >> arr[i];
		++i;
	}
	i = 0;
	try
	{
		time = atoi(arr[i].c_str());
	}
	catch (...)
	{
		time = 0;
	}
	i++;
	try
	{
		mH = (float)atof(arr[i].c_str());
	}
	catch (...)
	{
		mH = 0;
	}
	i++;
	try
	{
		mD = (float)atof(arr[i].c_str());
	}
	catch (...)
	{
		mD = 0;
	}
	i++;
	try
	{
		mE = (float)atof(arr[i].c_str());
	}
	catch (...)
	{
		mE = 0;
	}
	i++;
	try
	{
		mA = (float)atof(arr[i].c_str());
	}
	catch (...)
	{
		mA = 0;
	}
	i++;
	try
	{
		mT = (float)atof(arr[i].c_str());
	}
	catch (...)
	{
		mT = 0;
	}
	i++;
	try
	{
		mU = (float)atof(arr[i].c_str());
	}
	catch (...)
	{
		mU = 0;
	}

	H[time] = mH;
	D[time] = mD;
	E[time] = mE;
	A[time] = mA;
	T[time] = mT;
	U[time] = mU;

	/**/


	if ((minElevation > 10.0f) && (mE <= 10.0f))
	{
		alt10Elevation = mH;
	}
	if (((minElevation < 0) || (minElevation > mE)) && (time>60))
		minElevation = mE;
	if (maxAltitude < mH)
	{
		maxAltitude = mH;
		endOfAscent = time;
		endOfAscentPoint=H.size();
	}
		
	if (maxDistance < mD)
		maxDistance = mD;

	
}

map<int, float>::iterator RAWData::getIteratorByPoint(int point)
{
	map<int, float>::iterator i = H.begin();
	advance(i, point);
	return i;
}

map<int, float>::iterator RAWData::getIteratorByTimePoint(int time)
{
	map<int, float>::iterator i = H.begin();
	while (((*i).first) < time)
		i++;
	return i;
}

int RAWData::getPointByIterator(map<int, float>::iterator time)
{
	int i=0;
	map<int, float>::iterator it = H.begin();
	while (((*it).first) < (*time).first)
	{
		i++;
		it++;
	}
	return i;
}

int RAWData::getNumSpikes()
{
	return 0;
}
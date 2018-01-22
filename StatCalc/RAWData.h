#include "stdafx.h"

#ifndef RAWDATA_H
#define RAWDATA_H

class RAWData
{
public:
	RAWData();
	~RAWData(){};
	void addString(string str);
	int getSoundingTime();
	float getGroundTemperature();

	float getMinTemperature();
	float getMinTemperature(float Hthr);

	//Количество выбросов(по производной)
	int getNumSpikes();

	inline float getMaxAltitude()
	{
		return maxAltitude;
	}
	inline float getMaxDistance()
	{
		return maxDistance;
	}
	inline float getMinElevation()
	{
		return minElevation;
	}
	inline float getAlt10Elevation()
	{
		return alt10Elevation;
	}

	int getEndOfAscent()
	{
		return endOfAscent;
	}

	int getEndOfAscentPoint()
	{
		return endOfAscentPoint;
	}

	int getPointByIterator(map<int, float>::iterator time);
	map<int, float>::iterator getIteratorByPoint(int point);
	
	map<int, float>::iterator getIteratorByTimePoint(int time);

	map<int,float> H, D, E, A, T, U;
private:
	//float groundTemp;
	int endOfAscent;
	int endOfAscentPoint;
	float maxAltitude;
	float maxDistance;
	float minElevation;
	float alt10Elevation;
};

#endif
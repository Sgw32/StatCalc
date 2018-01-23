#include "stdafx.h"
#include "RAWData.h"

#ifndef WORKLAYER_H
#define WORKLAYER_H

/*

Рабочий слой принимает на вход все данные из RAW за слой.
Можно вычислить среднее и СКО.

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
	float medium(int start, int end)
	{
		float res = 0;
		map<int, float>::iterator it;
		map<int, float>::iterator its = mData.begin();
		advance(its, start);
		map<int, float>::iterator ite = mData.begin();
		advance(ite, end + 1);
		for (it = its; it != ite; it++)
		{
			res += (*it).second;
		}
		return res / (end - start +1);
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
	float computeStDev(int start, int end)
	{
		map<int, float>::iterator it;
		map<int, float>::iterator its = mData.begin();
		advance(its, start);
		map<int, float>::iterator ite = mData.begin();
		advance(ite, end + 1);
		float m = medium(start, end);
		float res = 0;
		for (it = its; it != ite; it++)
		{
			res += ((*it).second - m)*((*it).second - m);
		}
		res /= (end - start + 1);
		res = sqrt(res);
		return res;
	}
	pair<float, float> computeError(int start, int end) //sigma*2, sigma*3
	{
		int nout3, nout2;
		int np = end - start + 1;
		nout2 = nout3 = 0;
		float sigma = computeStDev(start, end);
		float sigma2 = sigma * 2;
		float sigma3 = sigma * 3;
		map<int, float>::iterator it;
		map<int, float>::iterator its = mData.begin();
		advance(its, start);
		map<int, float>::iterator ite = mData.begin();
		advance(ite, end+1);
		for (it = its; it != ite; it++)
		{
			if (fabs((*it).second) > sigma2)
			{
				nout2++;
			}
			if (fabs((*it).second) > sigma3)
			{
				nout3++;
			}
		}
		pair<float, float> res;
		res.first = ((float)nout2) / ((float)np);
		res.second = ((float)nout3) / ((float)np);
		return res;
	}
	map<int, float> mData;
};
#endif
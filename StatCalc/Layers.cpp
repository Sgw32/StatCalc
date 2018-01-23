#include "stdafx.h"
#include "Layers.h"

Layers::Layers()
{

}

Layers::~Layers()
{

}

void Layers::loadRAWData(RAWData* rawdata)
{
	rDa = rawdata;
}

void Layers::makeLayers()
{
	map<int, float>::iterator np = rDa->H.begin(); //перва€ €чейка сло€
	int shag = 5000; //шаг
	int tshag = 200;
	float h0 = 0; //нижн€€ граница сло€
	map<int, float>::iterator n = rDa->H.begin();
	int i1 = distance(rDa->H.begin(), n);
	int i2 = distance(rDa->H.begin(), rDa->getIteratorByTimePoint(rDa->getEndOfAscent()));
	while ((i1-i2)<0)
	{
		float h1 = h0 + shag; //верхн€€ граница сло€

		map<int, float>::iterator nfH = Fv(h1, 5, rDa->getEndOfAscent()); //¬ысота соответствующа€ новому концу сло€
		int time = (*nfH).first; // ¬рем€, соответствующее новому концу сло€
		int timen = time + tshag;
		map<int, float>::iterator nfT = FvT(timen, 1, rDa->getEndOfAscent());

		map<int, float>::iterator n0 = np;
		n = nfT;

		timeHLayersStart[(*n0).first] = (*n0).second;
		//for (i = rDa->H.begin(); i != rDa->H.end(); i++)
		timeHLayersEnd[(*nfT).first] = (*nfT).second;
		timen = time - tshag;
		np = FvT(timen, 1, rDa->getEndOfAscent());
		h0 = h1;
		i1 = distance(rDa->H.begin(), n);
	}

}

void Layers::make5000Layers()
{
	m5000Layers.push_back(0);
	map<int, float>::iterator np = rDa->H.begin(); //перва€ €чейка сло€
	int shag = 5000; //шаг
	int tshag = 200;
	float h0 = 0; //нижн€€ граница сло€
	map<int, float>::iterator n = rDa->H.begin();
	int i1 = distance(rDa->H.begin(), n);
	int i2 = distance(rDa->H.begin(), rDa->getIteratorByTimePoint(rDa->getEndOfAscent()));
	while ((i1 - i2) < 0)
	{
		float h1 = h0 + shag; //верхн€€ граница сло€
		map<int, float>::iterator nfH = Fv(h1, 5, rDa->getEndOfAscent());
		n = nfH;
		m5000Layers.push_back(rDa->getPointByIterator(nfH));
		i1 = distance(rDa->H.begin(), n);
		h0 = h1;
	}
}

vector<int> Layers::return5000Layers()
{
	return m5000Layers;
}

map<int, float>::iterator Layers::Fv(float H, int nc, int nfnl)
{
	map<int, float>::iterator it = rDa->H.begin();
	float Hres = (*it).second;
	while (Hres<H)
	{
		it++;
		if (it == rDa->H.end())
		{
			it--;
			return it;
		}
			
		Hres = (*it).second;
	}
	it--;
	float Hres2 = (*it).second;
	if (fabs(Hres - H) < fabs(Hres2 - H))
		it++;
	return it;
}

map<int, float>::iterator Layers::FvT(int T, int nc, int nfnl)
{
	map<int, float>::iterator it = rDa->H.begin();
	double Hres = (double)(*it).first;
	while (Hres<T)
	{
		it++;
		if (it == rDa->H.end())
		{
			it--;
			return it;
		}
			
		Hres = (*it).first;
	}
	it--;
	double Hres2 = (double)(*it).first;
	if (fabs(Hres - (double)T) < fabs(Hres2 - (double)T))
		it++;
	return it;
}

pair<map<int, float>, map<int, float>> Layers::returnLayers()
{
	pair<map<int, float>, map<int, float>> res;
	res.first = timeHLayersStart;
	res.second = timeHLayersEnd;
	return res;
}
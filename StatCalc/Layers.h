#include "stdafx.h"
#include "RAWData.h"

#ifndef LAYERS_H
#define LAYERS_H

class Layers
{
public:
	Layers();
	~Layers();
	void loadRAWData(RAWData* rawdata);
	void makeLayers();
	pair<map<int, float>, map<int, float>> returnLayers();
private:
	map<int, float>::iterator Fv(float H, int nc, int nfnl);
	map<int, float>::iterator FvT(int T, int nc, int nfnl);
	RAWData* rDa;
	map<int, float> timeHLayersStart;
	map<int, float> timeHLayersEnd;
};

#endif
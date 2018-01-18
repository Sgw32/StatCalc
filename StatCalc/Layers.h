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
	map<int,float> returnLayers();
private:
	RAWData* rDa;
	map<int, float> timeHLayers;
};

#endif
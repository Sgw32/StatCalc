#include "stdafx.h"
#include "RAWData.h"

#ifndef FILELOADER_H
#define FILELOADER_H

class FileLoader
{
public:
	FileLoader();
	~FileLoader();
	bool parseCommandLine(int argc, char *argv[]);
	string getOutName();
	void loadData();
	RAWData* getRAWData();
	string getRAWfile();
private:
	RAWData* rDa;
	string inputFile;
};

#endif
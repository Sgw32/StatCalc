#include "stdafx.h"
#include "FileLoader.h"

FileLoader::FileLoader()
{
	rDa = new RAWData();
}

FileLoader::~FileLoader()
{
	delete rDa;
}

void FileLoader::parseCommandLine(int argc, char *argv[])
{
	if (argc == 1)
	{
		inputFile = string(argv[1]);
	}
}

string FileLoader::getRAWfile()
{
	std::ifstream t(inputFile);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void FileLoader::loadData()
{
	string rawFile = getRAWfile();
	try
	{
		if (rawFile.length() > 0)
		{
			/*
			хяундмше дюммше гнмдхпнбюмхъ гю 05.11.2016 11:30
			опхгелмши береп (D V) :  22  6
			опхгелмне дюбкемхе : 1011.0
			пюяонкнфемхе ярюмжхх :
			ьхпнрю :  43 днкцнрю : 132
			бшянрю мюд спнбмел лнпъ :    90
			яхмнорхвеяйхи хмдейя ярюмжхх : 31977
			йнд накювмнярх :
			бпел     H      D      E      A     T  U
			*/
			
			unsigned int newl = rawFile.find('\n');
			for (int i = 0; i != 9; i++)
			{
				newl = rawFile.find('\n', newl) + 1;
			}

			while (newl < rawFile.length())
			{
				string last_str = rawFile.substr(newl, rawFile.find('\n', newl) - newl);
				rDa->addString(last_str);
				newl = rawFile.find('\n', newl) + 1;
			}

		}
	}
	catch (...)
	{

	}
}

RAWData* FileLoader::getRAWData()
{
	return rDa;
}
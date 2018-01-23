// StatCalc.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "FileLoader.h"
#include "RegressionCalc.h"
#include "Layers.h"
#include "Statistics.h"

int main(int argc, char *argv[])
{
	//Загрузим RAW файл. Обработаем консольные команды.
	FileLoader* fl = new FileLoader;
	fl->parseCommandLine(argc, argv);
	fl->loadData();
	RAWData* rda = fl->getRAWData();

	//Инициализируем калькулятор с регрессией
	RegressionCalc* rclc = new RegressionCalc();
	rclc->loadRAWData(rda);

	//Посчитаем слои
	Layers layers;
	layers.loadRAWData(rda);
	layers.makeLayers();
	layers.make5000Layers();
	pair<map<int, float>, map<int, float>> layerMap = layers.returnLayers();
	vector<int> m5000Layers = layers.return5000Layers();
	//Посчитаем статистику
	Statistics* stats = new Statistics();
	stats->loadRAWData(rda);
	stats->loadRegressionCalc(rclc);
	stats->loadLayers(layerMap);
	stats->load5000Layers(m5000Layers);

	stats->makeWorkLayers();
	stats->computeStatistics();

	//Память после всего этого всё равно будет очищена. Всем пока, было весело.
	system("pause");
	return 0;
}


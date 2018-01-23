#include "stdafx.h"
#include "minicsv.h"

#ifndef REPORTWRITER_H
#define REPORTWRITER_H

class ReportWriter
{
public:
	static ReportWriter& Instance()
	{
		// согласно стандарту, этот код ленивый и потокобезопасный
		static ReportWriter s;
		return s;
	}
	void init();
private:
	ReportWriter() 
	{
	}  // конструктор недоступен
	~ReportWriter() 
	{
	} // и деструктор

	// необходимо также запретить копирование
	ReportWriter(ReportWriter const&); // реализация не нужна
	ReportWriter& operator= (ReportWriter const&);  // и тут
};

#endif
#include "stdafx.h"
#include "minicsv.h"

#ifndef REPORTWRITER_H
#define REPORTWRITER_H

class ReportWriter
{
public:
	static ReportWriter& Instance()
	{
		// �������� ���������, ���� ��� ������� � ����������������
		static ReportWriter s;
		return s;
	}
	void init();
private:
	ReportWriter() 
	{
	}  // ����������� ����������
	~ReportWriter() 
	{
	} // � ����������

	// ���������� ����� ��������� �����������
	ReportWriter(ReportWriter const&); // ���������� �� �����
	ReportWriter& operator= (ReportWriter const&);  // � ���
};

#endif
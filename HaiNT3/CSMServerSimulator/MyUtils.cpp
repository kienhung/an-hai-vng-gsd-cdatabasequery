#include "StdAfx.h"
#include "MyUtils.h"

CMyUtils::CMyUtils(void)
{
}

CMyUtils::~CMyUtils(void)
{
}

void CMyUtils::DeCodeString(const CString &strIN, CString & strOUT)
{
	int lilength=strIN.GetLength();
	strOUT.GetBufferSetLength(lilength);
	for(int i=0;i<lilength;i++)
	{
		if(i%3==0)
			strOUT.SetAt(i,strIN.GetAt(i)-5);
		else if(i%2==0)
			strOUT.SetAt(i,strIN.GetAt(i)+3);
		else if(i%5==0)
			strOUT.SetAt(i,strIN.GetAt(i)-7);
		else
			strOUT.SetAt(i,strIN.GetAt(i)+2);
	}
}
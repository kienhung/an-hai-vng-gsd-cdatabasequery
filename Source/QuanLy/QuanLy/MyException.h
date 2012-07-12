#pragma once
#include <iostream>
using namespace std;

enum ExceptionCode {MY_SQL};

class CMyException : exception
{
private:
	TCHAR *m_strMessage;
	int m_iCode;
public:
	CMyException(TCHAR* strMessage, int iCode);
	CMyException(char* strMessage, int iCode);

	LPCTSTR GetMessage();
	int GetCode();
	~CMyException(void);
};

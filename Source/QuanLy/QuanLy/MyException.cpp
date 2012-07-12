#include "StdAfx.h"
#include "MyException.h"

CMyException::CMyException(TCHAR* strMessage, int iCode)
{
	m_iCode = -1;

	size_t ulSize = lstrlen(strMessage);
	m_strMessage = new TCHAR[ulSize + 1];

	if (NULL != m_strMessage) {
		_tcscpy_s(m_strMessage, ulSize + 1, strMessage);
		m_iCode = iCode;
	}
}

CMyException::~CMyException(void)
{
	if (NULL != m_strMessage) {
		delete[] m_strMessage;
	}
}

CMyException::CMyException(char* strMessage, int iCode) {

	m_iCode = -1;
	
	size_t ulLength = strlen(strMessage);
	m_strMessage = new TCHAR[ulLength + 1];

	if (NULL != m_strMessage) {
		for (size_t i = 0; i <= ulLength; i++) {
			m_strMessage[i] = strMessage[i];
		}
	}
}

LPCTSTR CMyException::GetMessage() {
	return m_strMessage;
}

int CMyException::GetCode() {
	return m_iCode;
}

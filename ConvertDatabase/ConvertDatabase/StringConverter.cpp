#include "StdAfx.h"
#include "StringConverter.h"

CStringConverter::CStringConverter(void)
{
	m_ptcStrOut = NULL;
	m_pcStrOut = NULL;
}

CStringConverter::~CStringConverter(void)
{
	if (NULL != m_ptcStrOut) {
		delete[] m_ptcStrOut;
	}
	if (NULL != m_pcStrOut) {
		delete[] m_pcStrOut;
	}
}

LPCTSTR CStringConverter::UTF8ToUnicode(char *pcStrIn) {

	if (NULL != m_ptcStrOut) {
		delete[] m_ptcStrOut;
	}

	if (NULL == pcStrIn) {
		return NULL;
	}

	int iLength = strlen(pcStrIn);

	if (0 == iLength ) {
		m_ptcStrOut = new TCHAR[1];
		if (NULL == m_ptcStrOut) {
			return NULL;
		}
		m_ptcStrOut[0] = L'\0';
		return m_ptcStrOut;
	}

	int iSize = MultiByteToWideChar(CP_UTF8, 0, pcStrIn, iLength, NULL, 0);

	m_ptcStrOut = new TCHAR[iSize + 1];
	if (NULL == m_ptcStrOut) {
		return NULL;
	}

	iSize = MultiByteToWideChar(CP_UTF8, 0, pcStrIn, iLength, m_ptcStrOut, iSize);

	if (iSize == 0) {
		delete[] m_ptcStrOut;
		return NULL;
	}

	m_ptcStrOut [iSize] = L'\0';

	return m_ptcStrOut;
}

char* CStringConverter::UnicodeToUTF8(LPCTSTR ptcStrIn) {

	if (NULL != m_pcStrOut) {
		delete[] m_pcStrOut;
	}

	if (NULL == ptcStrIn) {
		return NULL;
	}

	size_t uiLength = lstrlen(ptcStrIn);
	if (0 == uiLength) {
		m_pcStrOut = new char[1];
		if (NULL == m_pcStrOut) {
			return NULL;
		}

		m_pcStrOut[0] = '\0';
		return m_pcStrOut;
	}

	int iSize = WideCharToMultiByte(CP_UTF8, 0, ptcStrIn, uiLength, NULL, 0, NULL, NULL);
	if (0 == iSize) {
		return NULL;
	}

	m_pcStrOut = new char[iSize + 1];
	if (NULL == m_pcStrOut) {
		return NULL;
	}

	iSize = WideCharToMultiByte(CP_UTF8, 0, ptcStrIn, uiLength, m_pcStrOut, iSize, NULL, NULL);

	if (0 == iSize) 
	{
		delete[] m_pcStrOut;
		return NULL;
	}
	m_pcStrOut[iSize] = '\0';
	return m_pcStrOut;
}

char* CStringConverter::ConvertIntoUTF8(const wchar_t *pWideChar)
{
	char	*pUTF8Str;
	int		iLen,
			iNumByte = 0;

	iLen = wcslen(pWideChar);
	iNumByte = WideCharToMultiByte(CP_UTF8, 0, pWideChar, iLen, NULL, 0, NULL, NULL);

	if (iNumByte <= 0)
		return NULL;

	pUTF8Str = new char[iNumByte + 1];
	if (!pUTF8Str)
		return NULL;

	WideCharToMultiByte(CP_UTF8, 0, pWideChar, iLen, pUTF8Str, iNumByte, NULL, NULL);
	pUTF8Str[iNumByte] = 0;

	return pUTF8Str;
}
#pragma once

class CStringConverter
{
protected:
	LPTSTR m_ptcStrOut;
	char *m_pcStrOut;
public:
	CStringConverter(void);
	~CStringConverter(void);

	LPCTSTR UTF8ToUnicode(char *pcStrIn);
	char* UnicodeToUTF8(LPCTSTR ptcStrIn);

};

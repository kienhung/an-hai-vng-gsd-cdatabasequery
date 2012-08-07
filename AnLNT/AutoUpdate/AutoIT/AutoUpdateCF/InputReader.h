#pragma once

class CInputReader
{
protected:
	CString m_strInput;
	CString m_strToken;

public:
	CInputReader(LPCTSTR strInputFileName);
	BOOL Read();
	BOOL ReadSection( LPCTSTR strSectionName, LPTSTR strSourcePath, LPTSTR strLauncherPath);

	BOOL ReadAudition();
	BOOL ReadCrossfire();
	BOOL ReadFifaonline2();	

	virtual ~CInputReader(void);
};

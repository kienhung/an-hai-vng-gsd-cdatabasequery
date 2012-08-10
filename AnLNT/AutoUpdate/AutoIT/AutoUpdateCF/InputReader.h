#pragma once

#include "AutoUpdateTool.h"
#include <list>

using namespace std;

class CInputReader
{
protected:
	CString m_strInput;
	CString m_strToken;
	list<CAutoUpdateTool*> m_listAutoUpdateTool;
	HANDLE *m_pHandle;

	BOOL Run();

	BOOL ReadSection( LPCTSTR strSectionName, LPTSTR strSourcePath);
	BOOL ReadAudition();
	void AddItem( CLauncher * pAutoLauncher );
	BOOL ReadCrossfire();
	BOOL ReadFifaonline2();	

public:
	static DWORD WINAPI UpdateThreadFunction(PVOID pvParam);

	CInputReader(LPCTSTR strInputFileName);
	BOOL Read();
	virtual ~CInputReader(void);
};

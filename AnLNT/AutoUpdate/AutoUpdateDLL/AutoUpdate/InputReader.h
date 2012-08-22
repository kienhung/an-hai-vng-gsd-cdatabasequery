#pragma once

#include "AutoUpdateTool.h"
#include <list>

using namespace std;

class AFX_EXT_CLASS CInputReader
{
protected:

	CString m_strInput;
	CString m_strToken;

	list<CAutoUpdateTool*> m_listAutoUpdateTool;

	BOOL Run();

	BOOL ReadSection( LPCTSTR strSectionName, LPTSTR strSourcePath);
	void AddItem( CLauncher * pAutoLauncher );

	BOOL ReadSR();
	BOOL ReadWOT();
	BOOL ReadTLBB();
	BOOL ReadAudition();
	BOOL ReadCrossfire();
	BOOL ReadFifaonline2();	

public:

	CInputReader(LPCTSTR strInputFileName);
	BOOL Read();
	virtual ~CInputReader(void);
};

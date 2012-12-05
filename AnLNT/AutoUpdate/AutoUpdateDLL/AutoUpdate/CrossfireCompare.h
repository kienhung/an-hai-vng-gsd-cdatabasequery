#pragma once
#include "gamesourcecompare.h"

class CCrossfireCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);

	CString m_strGamePatchDirectory;
	CString m_strBackupDirectory;

public:
	CCrossfireCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CCrossfireCompare(void);
};

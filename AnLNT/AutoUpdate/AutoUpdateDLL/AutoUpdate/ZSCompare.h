#pragma once
#include "gamesourcecompare.h"

class CZSCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
	CString m_strNoCheckDirectory;
public:
	CZSCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CZSCompare(void);
};

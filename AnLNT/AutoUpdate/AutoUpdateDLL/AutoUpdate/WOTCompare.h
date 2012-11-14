#pragma once
#include "gamesourcecompare.h"

class CWOTCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
public:
	CWOTCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CWOTCompare(void);
};

#pragma once
#include "gamesourcecompare.h"

class CZSCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
public:
	CZSCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CZSCompare(void);
};

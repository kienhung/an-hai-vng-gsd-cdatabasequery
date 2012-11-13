#pragma once
#include "gamesourcecompare.h"

class CCrossfireCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
public:
	CCrossfireCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CCrossfireCompare(void);
};

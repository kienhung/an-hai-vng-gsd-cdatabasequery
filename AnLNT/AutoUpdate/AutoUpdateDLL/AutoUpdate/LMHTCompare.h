#pragma once
#include "gamesourcecompare.h"

class CLMHTCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);

public:
	CLMHTCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CLMHTCompare(void);
};

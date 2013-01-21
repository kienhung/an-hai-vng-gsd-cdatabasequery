#pragma once
#include "gamesourcecompare.h"

class C9DGCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);

public:
	C9DGCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~C9DGCompare(void);
};

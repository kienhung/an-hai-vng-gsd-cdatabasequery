#pragma once
#include "gamesourcecompare.h"

class CTBVCompare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
public:
	CTBVCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CTBVCompare(void);
};

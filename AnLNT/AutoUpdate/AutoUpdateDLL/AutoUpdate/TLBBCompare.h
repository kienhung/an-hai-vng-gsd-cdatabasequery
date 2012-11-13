#pragma once
#include "GameSourceCompare.h"

class CTLBBCompare:
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
public:
	CTLBBCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CTLBBCompare(void);
};

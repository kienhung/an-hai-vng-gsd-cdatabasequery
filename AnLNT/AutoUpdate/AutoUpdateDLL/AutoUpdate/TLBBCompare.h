#pragma once
#include "GameSourceCompare.h"

class CTLBBCompare:
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
	CString m_strNoCheckDirectory;
public:
	CTLBBCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CTLBBCompare(void);
};

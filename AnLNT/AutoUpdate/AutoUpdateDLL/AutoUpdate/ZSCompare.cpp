#include "StdAfx.h"
#include "ZSCompare.h"
#include <shlwapi.h>



CZSCompare::CZSCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{

}

CZSCompare::~CZSCompare(void)
{
}

BOOL CZSCompare::IsNeedCompare( LPCTSTR strFileName )
{

	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".log") == 0)
	{
		return FALSE;
	}

	PTSTR strSub = ::PathFindFileName(strFileName);
	if (lstrcmpi(strSub, L"QQLogin.dat") == 0 )
	{
		return FALSE;
	}

	return TRUE;
}

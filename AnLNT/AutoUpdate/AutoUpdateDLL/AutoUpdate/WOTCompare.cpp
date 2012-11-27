#include "StdAfx.h"
#include "WOTCompare.h"
#include <shlwapi.h>
#include "MyUtils.h"



CWOTCompare::CWOTCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{

}

CWOTCompare::~CWOTCompare(void)
{
}

BOOL CWOTCompare::IsNeedCompare( LPCTSTR strFileName )
{
	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".log") == 0 ||
		lstrcmpi(strExtesion, L".bak") == 0 || 
		lstrcmpi(strExtesion, L".killme") == 0)
	{
		return FALSE;
	}

	if (lstrcmpi(strExtesion, L".patch") == 0 )
	{
		if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"Updates"))
		{
			return FALSE;
		}
	}
	return TRUE;
}

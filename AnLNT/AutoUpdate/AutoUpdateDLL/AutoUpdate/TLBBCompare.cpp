#include "StdAfx.h"
#include "TLBBCompare.h"
#include "MyUtils.h"
#include <shlwapi.h>

CTLBBCompare::CTLBBCompare(LPCTSTR strNewSource, LPCTSTR strOldSource)
:CGameSourceCompare(strNewSource, strOldSource)
{
	m_strNoCheckDirectory.Format(L"%s\\%s", strNewSource, L"gamepatch");
}

CTLBBCompare::~CTLBBCompare(void)
{
}

BOOL CTLBBCompare::IsNeedCompare( LPCTSTR strFileName )
{
	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".log") == 0)
	{
		return FALSE;
	}

	CString strTemp = CString(strFileName).Left(m_strNoCheckDirectory.GetLength());
	if (strTemp.CompareNoCase(m_strNoCheckDirectory) == 0)
	{
		return FALSE;
	}

	if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"Patch"))
	{
		PTSTR strExtesion = ::PathFindExtension(strFileName);
		if (lstrcmpi(strExtesion, L".txt") == 0 || lstrcmpi(strExtesion, L".xzip") == 0)
		{
			return FALSE;
		}
	}

	PTSTR strSub = ::PathFindFileName(strFileName);
	if (lstrcmpi(strSub, L"System.cfg") == 0)
	{
		return FALSE;
	}

	return TRUE;
}

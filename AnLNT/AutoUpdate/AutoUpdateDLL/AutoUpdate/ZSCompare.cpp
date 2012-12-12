#include "StdAfx.h"
#include "ZSCompare.h"
#include <shlwapi.h>



CZSCompare::CZSCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{
	m_strNoCheckDirectory.Format(L"%s\\%s", strNewSource, L"userdata");
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

	CString strTemp = CString(strFileName).Left(m_strNoCheckDirectory.GetLength());
	if (strTemp.CompareNoCase(m_strNoCheckDirectory) == 0)
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

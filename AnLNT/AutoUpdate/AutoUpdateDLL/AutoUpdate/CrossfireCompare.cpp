#include "StdAfx.h"
#include "CrossfireCompare.h"
#include <shlwapi.h>
#include "MyUtils.h"

CCrossfireCompare::CCrossfireCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{
	m_strGamePatchDirectory.Format(L"%s\\%s", strNewSource, L"gamepatch");
	m_strBackupDirectory.Format(L"%s\\%s", strNewSource, L"backup");
}

CCrossfireCompare::~CCrossfireCompare(void)
{
}

BOOL CCrossfireCompare::IsNeedCompare( LPCTSTR strFileName )
{
	CString strTemp = CString(strFileName).Left(m_strGamePatchDirectory.GetLength());
	if (strTemp.CompareNoCase(m_strGamePatchDirectory) == 0)
	{
		return FALSE;
	}

	strTemp = CString(strFileName).Left(m_strBackupDirectory.GetLength());
	if (strTemp.CompareNoCase(m_strBackupDirectory) == 0)
	{
		return FALSE;
	}


	if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"XTrap"))
	{
		return FALSE;
	}

	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".slg") == 0 || lstrcmpi(strExtesion, L".log") == 0)
	{
		return FALSE;
	}
	return TRUE;
}

#include "StdAfx.h"
#include "GameSourceCompare.h"
#include "MyUtils.h"
#include "MyPath.h"
#include <shlwapi.h>
#include <algorithm>

CGameSourceCompare::CGameSourceCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CFolderCompare(strNewSource, strOldSource)
{
	Init();
	
}

CGameSourceCompare::~CGameSourceCompare(void)
{
}

BOOL CGameSourceCompare::Init()
{
	m_bHasUpdate = FALSE;
	m_strResultFilePath = L"";
	m_strGamePatchDirectory.Format(L"%s\\%s", m_strNewSource, L"gamepatch");

	return TRUE;
}

BOOL CGameSourceCompare::Compare( LPCTSTR strResultFilePath )
{
	Init();
	m_strResultFilePath = strResultFilePath;

	if (FALSE == CFolderCompare::Compare(strResultFilePath))
	{
		CString strError;
		strError.Format(L"Failure to compare source game with Error %u", GetLastError());
		CMyUtils::WriteErrorLog(strError);

		return FALSE;
	}
	return TRUE;
}

BOOL CGameSourceCompare::HasUpdate()
{
	return m_bHasUpdate;
}

BOOL CGameSourceCompare::DeleteResultFile()
{
	if (FALSE == ::DeleteFile(m_strResultFilePath))
	{
		CString strError;
		strError.Format(L"Failure to delete result file with Error %u", GetLastError());
		CMyUtils::WriteErrorLog(strError);

		return FALSE;
	}
	return TRUE;
}

BOOL CGameSourceCompare::IsNeedCompare( LPCTSTR strFileName )
{
	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".log") == 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGameSourceCompare::ProcessFile( LPCTSTR strFileName )
{
	if (TRUE == m_bHasUpdate)
	{
		return TRUE;
	}

	if (TRUE == IsUnnecessaryToCheckForAllGames(strFileName))
	{
		return TRUE;
	}

	if (FALSE == IsNeedCompare(strFileName))
	{
		return TRUE;
	}

	if (FALSE == CheckFileExist(strFileName))
	{
		if (FALSE == WriteFile(strFileName, m_hResultFile))
		{
			return FALSE;
		}
		m_bHasUpdate = TRUE;
	}
	else
	{
		CMyPath myPath;
		CString strOldFileName = myPath.TransferSourcePath(m_strNewSource, m_strOldSource, strFileName);

		if (FALSE == CheckSum(strFileName, strOldFileName))
		{
			if (FALSE == WriteFile(strFileName, m_hTempFile))
			{
				return FALSE;
			}
			m_bHasUpdate = TRUE;
		}
	}
	return TRUE;
}

BOOL CGameSourceCompare::IsUnnecessaryToCheckForAllGames( LPCTSTR strFileName )
{
	if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"logs"))
	{
		return TRUE;
	}

	PTSTR strSub = ::PathFindFileName(strFileName);
	if (lstrcmpi(strSub, L"gmautoupdate.fls") == 0 ||
		lstrcmpi(strSub, L"autoupdate.fls") == 0 ||
		lstrcmpi(strSub, L"rootfolder.enc") == 0)
	{
		return TRUE;
	}

	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".torrent") == 0
		|| lstrcmpi(strExtesion, L".log") == 0)
	{
		return TRUE;
	}

	CString strTemp = CString(strFileName).Left(m_strGamePatchDirectory.GetLength());
	if (strTemp.CompareNoCase(m_strGamePatchDirectory) == 0)
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CGameSourceCompare::IsFileInListFilesNoCheck( LPCTSTR strFileName )
{
	CString strSubFileName = ::PathFindFileName(strFileName);
	vector<CString>::iterator it = find (lstFilesNoCheck.begin(), lstFilesNoCheck.end(), strSubFileName);

	if (it != lstFilesNoCheck.end())
	{
		return TRUE;
	}

	return FALSE;
}

#include "StdAfx.h"
#include "GameSourceCompare.h"
#include "MyUtils.h"
#include "MyPath.h"

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
	return TRUE;
}

BOOL CGameSourceCompare::ProcessFile( LPCTSTR strFileName )
{
	if (TRUE == m_bHasUpdate)
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

#include "StdAfx.h"
#include "BlackListReader.h"


CBlackListReader::CBlackListReader(void)
{
	m_bIsConnected = m_blackListDAO.ConnectToDB("root", "", "localhost", "ddm");

}

CBlackListReader::~CBlackListReader(void)
{

}

BOOL CBlackListReader::ProcessItem( LPCTSTR strItemText )
{

	::OutputDebugString(strItemText);
	::OutputDebugStringA("\n");

	if (TRUE == m_blackListDAO.CheckBlackExist(strItemText ))
	{
		if (FALSE == m_blackListDAO.UpdateAddedBy(strItemText, 1, 0))
		{
			return FALSE;
		}
	}
	else
	{
		if (FALSE == m_blackListDAO.AddBlackWeb(strItemText))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CBlackListReader::Read( LPCTSTR strFilePath )
{
	if (FALSE == m_bIsConnected)
	{
		return FALSE;
	}

	if (FALSE == m_blackListDAO.UpdateAddedBy(L"%%", 0, 1))
	{
		return FALSE;
	}

	CStdioFile fileReader;
	CFileException fileException;

	if (FALSE == fileReader.Open(strFilePath, CFile::modeRead | CFile::shareDenyNone , &fileException))
	{
		return FALSE;
	} 

	CString strItemText;
	while (fileReader.ReadString(strItemText))
	{
		if (FALSE == ProcessItem(strItemText))
		{
			return TRUE;
		}
	}

	return m_blackListDAO.RemoveInvalidURL();
}

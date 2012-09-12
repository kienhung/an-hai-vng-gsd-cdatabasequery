#include "StdAfx.h"
#include "BlackListReader.h"
#include <fstream>
#include <string>

using namespace std;

CBlackListReader::CBlackListReader(void)
{
	m_bIsConnected = m_blackListDAO.ConnectToDB("root", "", "localhost", "ddm");
}

CBlackListReader::~CBlackListReader(void)
{

}


BOOL CBlackListReader::Read( LPCTSTR strFilePath )
{
	if (FALSE == m_bIsConnected)
	{
		return FALSE;
	}

	ifstream input (strFilePath, ios::in);
	if (false == input.is_open())
	{
		return FALSE;
	}

	if (FALSE == m_blackListDAO.UpdateAddedBy("%%", 0, 1))
	{
		return FALSE;
	}

	string strLine;
	while (getline(input, strLine))
	{
		if (FALSE == ProcessURL(strLine.c_str()))
		{
			return FALSE;
		}
	}

	return m_blackListDAO.RemoveInvalidURL();
}

BOOL CBlackListReader::ProcessURL( const char* strURL )
{
	if (TRUE == m_blackListDAO.CheckURLExist(strURL))
	{
		if (FALSE == m_blackListDAO.UpdateAddedBy(strURL, 1, 0))
		{
			return FALSE;
		}
	} 
	else 
	{
		if (FALSE == m_blackListDAO.InsertURL(strURL))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CBlackListReader::CreateTempFile( CString &cstrOut )
{
	TCHAR strTempFileName[MAX_PATH];  
	TCHAR strTempPath[MAX_PATH];

	if (0 == ::GetTempPath(MAX_PATH, strTempPath)) {
		return FALSE;
	}

	if (0 == ::GetTempFileName(strTempPath, L"hkt", 0,  strTempFileName)) {
		return FALSE;
	}

	cstrOut = strTempFileName;
	return TRUE;
}

#include "StdAfx.h"
#include "LogFinder.h"
#include "MailProjectUtility.h"
#include "MyUtils.h"
#include <algorithm>

CLogFinder::CLogFinder(void)
{
}

CLogFinder::~CLogFinder(void)
{
}

std::string CLogFinder::GetLastLogFile( LPCTSTR strLogDirectory )
{
	m_strLastLog.clear();

	ZeroMemory(&m_ftMaxWriteName, sizeof(FILETIME));

	CFolderProcesser::Process(strLogDirectory);
	sort(lstLog.begin(), lstLog.end());

	char * strUTF8FileName = CMyUtils::ConvertWideCharToUTF8(lstLog.back());

	if (strUTF8FileName != NULL)
	{
		m_strLastLog = strUTF8FileName;
		delete [] strUTF8FileName;
	}

	return m_strLastLog;
}

BOOL CLogFinder::ProcessFile( LPCTSTR strFileName )
{

	lstLog.push_back(strFileName);

	//FILETIME ftTempWriteTime;
	//ZeroMemory(&ftTempWriteTime, sizeof(FILETIME));

	//if (TRUE == CMailProjectUtility::GetModifyTime(strFileName, ftTempWriteTime))
	//{
	//	if (m_strLastLog.empty() == true || CompareFileTime(&ftTempWriteTime, &m_ftMaxWriteName) > 0)
	//	{
	//		char * strUTF8FileName = CMyUtils::ConvertWideCharToUTF8(strFileName);

	//		if (strUTF8FileName != NULL)
	//		{
	//			m_strLastLog = strUTF8FileName;
	//			memcpy(&m_ftMaxWriteName, &ftTempWriteTime, sizeof(FILETIME));

	//			delete [] strUTF8FileName;
	//		}
	//	}
	//}
	return TRUE;
}

#include "StdAfx.h"
#include "LogFileInfo.h"

CLogFileInfo::CLogFileInfo(void)
{
	Init();
}

CLogFileInfo::~CLogFileInfo(void)
{
}

void CLogFileInfo::Init()
{
	m_strFileName = L"";
	ZeroMemory(&m_ftWriteTime, sizeof(FILETIME));

}

//vector<CLogFileInfo> CLogFileInfo::ListAll( LPCTSTR strDirectory )
//{
//	vector<CLogFileInfo> vLogFileInfo;
//	vLogFileInfo.reserve(NUM_FILES);
//
//	
//	return vLogFileInfo;
//}

#include "StdAfx.h"
#include "GlobalClass.h"
#include "MyPath.h"
#include <shlwapi.h>


#pragma comment (lib, "lib/Log.lib")

CMyCriticalSection CGlobalClass::m_sCrriticalSection;

CGlobalClass::CGlobalClass(void)
{
	CMyPath pathUtils;
	CString strLogDir = pathUtils.GetExeFilePath() + CString(L"\\log");
	m_logWriter.Initialize(strLogDir);

	m_strExeDirectory = PrepareExeDirectory();
	m_strConfigDirectory = m_strExeDirectory + CString("\\config");
}

CGlobalClass::~CGlobalClass(void)
{
}

CGlobalClass* CGlobalClass::GetInstance()
{
	m_sCrriticalSection.Lock();
	static CGlobalClass instance;
	m_sCrriticalSection.Unlock();

	return &instance;
}

CLogWriter * CGlobalClass::GetLogWriter()
{
	return &m_logWriter;
}

CString CGlobalClass::PrepareExeDirectory()
{
	TCHAR strModulePath[MAX_PATH]={0};
	if (0 == ::GetModuleFileName(NULL, strModulePath, MAX_PATH)) {
		return L"";
	}
	if (FALSE == ::PathRemoveFileSpec(strModulePath)) {
		return L"";
	}
	return strModulePath;
}

const CString& CGlobalClass::GetExeDirectory()
{
	return m_strExeDirectory;
}

const CString& CGlobalClass::GetConfigDirectory()
{
	return m_strConfigDirectory;
}



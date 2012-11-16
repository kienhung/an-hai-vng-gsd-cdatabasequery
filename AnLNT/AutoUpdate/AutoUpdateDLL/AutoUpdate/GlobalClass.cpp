#include "StdAfx.h"
#include "GlobalClass.h"
#include "MyPath.h"


#pragma comment (lib, "lib/Log.lib")

CMyCriticalSection CGlobalClass::m_sCrriticalSection;

CGlobalClass::CGlobalClass(void)
{
	CMyPath pathUtils;
	CString strLogDir = pathUtils.GetExeFilePath() + CString(L"\\log");
	m_logWriter.Initialize(strLogDir);
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



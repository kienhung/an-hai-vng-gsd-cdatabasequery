#include "StdAfx.h"
#include "InputReader.h"
#include "AutoUpdateTool.h"
#include "CrossfireAutoLauncher.h"
#include "Fifa2AutoLauncher.h"
#include "AuditionAutoLauncher.h"
#include "Launcher.h"

CInputReader::CInputReader( LPCTSTR strInputFileName )
{

	m_strInput = strInputFileName;
	m_pHandle = NULL;

	SYSTEMTIME time;
	GetLocalTime(&time);

	m_strToken.Format(L"%02u-%02u-%u-%02uh%02u", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);

}

BOOL CInputReader::Read()
{
	ReadAudition();
	ReadCrossfire();
	ReadFifaonline2();
	
	Run();
	return TRUE;
}



CInputReader::~CInputReader(void)
{

	if (m_pHandle != NULL) {
		delete[] m_pHandle;
	}

	list<CAutoUpdateTool*>::iterator it;

	for (it = m_listAutoUpdateTool.begin(); it != m_listAutoUpdateTool.end(); it++) {

		CAutoUpdateTool *pAutoUpdateTool = *it;

		if (NULL != pAutoUpdateTool) {

			delete[] pAutoUpdateTool;
			*it = NULL;
		}
	}
}

BOOL CInputReader::ReadSection( LPCTSTR strSectionName, LPTSTR strSourcePath )
{
	DWORD dwCount = ::GetPrivateProfileString(strSectionName, L"source", NULL, strSourcePath, MAX_PATH, m_strInput);

	if (dwCount <= 0) {
		return FALSE;
	}

	return TRUE;
}

BOOL CInputReader::ReadAudition()
{

	TCHAR strSourcePath[MAX_PATH];

	if (FALSE == ReadSection(L"Audition", strSourcePath)) {
		return FALSE;
	}
	
	CLauncher *pAutoLauncher = new CAuditionAutoLauncher(strSourcePath);

	AddItem(pAutoLauncher);

	return TRUE;
}

BOOL CInputReader::ReadCrossfire()
{

	TCHAR strSourcePath[MAX_PATH];

	if (FALSE == ReadSection(L"Crossfire", strSourcePath)) {
		return FALSE;
	}

	CLauncher *pAutoLauncher = new CCrossfireAutoLauncher(strSourcePath);
	AddItem(pAutoLauncher);

	return TRUE;
}

BOOL CInputReader::ReadFifaonline2()
{

	TCHAR strSourcePath[MAX_PATH];

	if (FALSE == ReadSection(L"Fifaonline2", strSourcePath)) {
		return FALSE;
	}

	CLauncher *pAutoLauncher = new CFifa2AutoLauncher(strSourcePath);
	AddItem(pAutoLauncher);

	return TRUE;
}

void CInputReader::AddItem( CLauncher * pAutoLauncher )
{
	CAutoUpdateTool *pAutoUpdateTool = new CAutoUpdateTool();
	pAutoUpdateTool->Create(pAutoLauncher, m_strToken);
	m_listAutoUpdateTool.push_back(pAutoUpdateTool);
}

BOOL CInputReader::Run()
{

	list<CAutoUpdateTool*>::iterator it;
	if (m_listAutoUpdateTool.size() == 0) {
		return FALSE;
	}

	if (m_pHandle != NULL) {
		delete[] m_pHandle;
	}

	m_pHandle = new HANDLE[m_listAutoUpdateTool.size()];
	int iCount = 0;

	for (it = m_listAutoUpdateTool.begin(); it != m_listAutoUpdateTool.end(); it++) {

		CAutoUpdateTool *pAutoUpdateTool = *it;

		if (NULL != pAutoUpdateTool) {

			m_pHandle[iCount] = ::CreateThread(NULL, 0,  CInputReader::UpdateThreadFunction, pAutoUpdateTool, 0, NULL);
			iCount++;
		}
	}

	::WaitForMultipleObjects(iCount, m_pHandle, TRUE, INFINITE);
	for (int i = 0; i < iCount; i++) {
		::CloseHandle(m_pHandle[i]);
	}

	return TRUE;
}

DWORD WINAPI CInputReader::UpdateThreadFunction( PVOID pvParam )
{

	CAutoUpdateTool *pAutoUpdateTool = (CAutoUpdateTool*)pvParam;

	if (pAutoUpdateTool->Update() == FALSE) {
		_tprintf(L"%s Fail\n", pAutoUpdateTool->GetName());
	}

	return 0;
}

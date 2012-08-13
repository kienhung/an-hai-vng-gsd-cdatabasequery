#include "StdAfx.h"
#include "InputReader.h"
#include "AutoUpdateTool.h"
#include "CrossfireAutoLauncher.h"
#include "Fifa2AutoLauncher.h"
#include "AuditionAutoLauncher.h"
#include "TLBBAutoLauncher.h"
#include "Launcher.h"

CInputReader::CInputReader( LPCTSTR strInputFileName )
{

	m_strInput = strInputFileName;

	SYSTEMTIME time;
	GetLocalTime(&time);

	m_strToken.Format(L"%u-%02u-%02u %02uh%02u",  time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute);
}

BOOL CInputReader::Read()
{
	ReadTLBB();
	ReadAudition();
	ReadCrossfire();
	ReadFifaonline2();
	
	Run();
	return TRUE;
}



CInputReader::~CInputReader(void)
{


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

	for (it = m_listAutoUpdateTool.begin(); it != m_listAutoUpdateTool.end(); it++) {

		CAutoUpdateTool *pAutoUpdateTool = *it;

		if (NULL != pAutoUpdateTool) {
			
			if (pAutoUpdateTool->Update() == FALSE) {
				_tprintf(L"%s Fail\n", pAutoUpdateTool->GetName());
			}
			
		}
	}

	return TRUE;
}

BOOL CInputReader::ReadTLBB()
{

	TCHAR strSourcePath[MAX_PATH];

	if (FALSE == ReadSection(L"TLBB", strSourcePath)) {
		return FALSE;
	}

	CLauncher *pAutoLauncher = new CTLBBAutoLauncher(strSourcePath);
	AddItem(pAutoLauncher);

	return TRUE;

}

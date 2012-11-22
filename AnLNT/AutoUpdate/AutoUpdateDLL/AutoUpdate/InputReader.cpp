#include "StdAfx.h"
#include "InputReader.h"
#include "AutoUpdateTool.h"
#include "CrossfireAutoLauncher.h"
#include "Fifa2AutoLauncher.h"
#include "AuditionAutoLauncher.h"
#include "TLBBAutoLauncher.h"
#include "Launcher.h"
#include "WOTAutoLauncher.h"
#include "LMHTAutoLauncher.h"

CInputReader::CInputReader( LPCTSTR strInputFileName )
{

	m_strInput = strInputFileName;

	SYSTEMTIME time;
	GetLocalTime(&time);

	//m_strToken.Format(L"%u-%02u-%02u %02uh%02u",  time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute);
	m_strToken.Format(L"%u-%02u-%02u", time.wDay , time.wMonth, time.wYear);
}

BOOL CInputReader::Read()
{
	//new game here
	const TCHAR * arrStrGameList[] = {L"TLBB", L"AU2", L"CF", L"FF", L"WOT", L"LOL"};
	size_t stNumberOfGamels = sizeof(arrStrGameList)/sizeof(const char*);
	for (size_t i = 0; i < stNumberOfGamels; i++)
	{
		TCHAR strSourcePath[MAX_PATH] = {0};
		TCHAR strCCSourcePath[MAX_PATH] = {0};

		if (TRUE == ReadSection(arrStrGameList[i], strSourcePath, strCCSourcePath))
		{
			CLauncher *pAutoLauncher = NULL;

			if (lstrcmpi(arrStrGameList[i], L"TLBB") == 0)
			{
				pAutoLauncher = new CTLBBAutoLauncher(strSourcePath);
			} 
			else if (lstrcmpi(arrStrGameList[i], L"AU2") == 0)
			{
				pAutoLauncher = new CAuditionAutoLauncher(strSourcePath);
			}
			else if (lstrcmpi(arrStrGameList[i], L"CF") == 0)
			{
				pAutoLauncher = new CCrossfireAutoLauncher(strSourcePath);
			}
			else if (lstrcmpi(arrStrGameList[i], L"FF") == 0)
			{
				pAutoLauncher = new CFifa2AutoLauncher(strSourcePath);
			}
			else if (lstrcmpi(arrStrGameList[i], L"WOT") == 0)
			{
				pAutoLauncher = new CWOTAutoLauncher(strSourcePath);
			}
			else if(lstrcmpi(arrStrGameList[i], L"LOL") == 0)
			{
				pAutoLauncher = new CLMHTAutoLauncher(strSourcePath);
			}
			//new game here

			if (pAutoLauncher != NULL)
			{
				AddItem(pAutoLauncher, strCCSourcePath);
			}
		}
	}
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

void CInputReader::AddItem( CLauncher * pAutoLauncher , LPCTSTR strCCSourcePath )
{
	CAutoUpdateTool *pAutoUpdateTool = new CAutoUpdateTool();
	pAutoUpdateTool->Create(pAutoLauncher, m_strToken, strCCSourcePath);
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

BOOL CInputReader::ReadSection( LPCTSTR strSectionName, LPTSTR strSourcePath, LPTSTR strCCSource )
{
	DWORD dwCount = ::GetPrivateProfileString(strSectionName, L"source", NULL, strSourcePath, MAX_PATH, m_strInput);

	if (dwCount <= 0) 
	{
		return FALSE;
	}

	dwCount = ::GetPrivateProfileString(strSectionName, L"cc", NULL, strCCSource, MAX_PATH, m_strInput);

	if (dwCount <= 0)
	{
		return FALSE;
	}

	return TRUE;
}


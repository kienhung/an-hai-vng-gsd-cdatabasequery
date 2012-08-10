// AutoUpdateCF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutoUpdate.h"
#include "MyPath.h"
#include "InputReader.h"
#include "Fifa2AutoLauncher.h"
#include "AuditionAutoLauncher.h"
#include "CrossfireAutoLauncher.h"
#include "AutoUpdateTool.h"
#include "FolderCompare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CWinApp theApp;

using namespace std;



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{

		/*
		CFolderCompare folderCompare(L"D:\\GameUpdate\\Audition", L"D:\\GameUpdate\\Audition_1");
		if (FALSE == folderCompare.Compare(L"D:\\test.txt")) {
			_tprintf(L"Fail\n");
			return FALSE;
		}
		_tprintf(L"OK\n");
		*/

		/*
		TCHAR m_strSource[] = L"D:\\GameUpdate\\crossfire";
		TCHAR m_strLauncher[] = L"D:\\GameUpdate\\crossfire\\Crossfire.exe";


		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;

		if (FALSE == ::CreateProcess(m_strLauncher, NULL, NULL, NULL, FALSE, 0, NULL, m_strSource, &si, &pi)) {
			_tprintf(L"Fail\n");
			return FALSE;
		}

		_tprintf(L"OK\n");
		*/

		//TCHAR strSource[] = L"D:\\GameUpdate\\Fifa2";
		//CLauncher *pLauncher = new CFifa2AutoLauncher(strSource);

		//TCHAR strSource[] = L"D:\\GameUpdate\\Audition";
		//CLauncher *pLauncher = new CAuditionAutoLauncher(strSource);

		/*
		TCHAR strSource[] = L"D:\\GameUpdate\\crossfire";
		CLauncher *pLauncher = new CCrossfireAutoLauncher(strSource);


		CAutoUpdateTool updateTool;
		updateTool.Create(pLauncher, L"06-08-2012-16h52");

		if (FALSE == updateTool.Update()) {
			_tprintf(L"Fail\n");
		} else {
			_tprintf(L"OK\n");
		}
		/*
		if (pLauncher != NULL) {
			if (pLauncher->Run()) {
				_tprintf(L"OK\n");
			} else {
				_tprintf(L"Fail\n");
			}
		}

		if (pLauncher != NULL) {
			delete pLauncher;
		}
		
		
		*/

		CMyPath myPath;

		CString strExeFilePath = myPath.GetExeFilePath();
		CString strInputFilePath = strExeFilePath + L"\\input.ini";

		CInputReader reader(strInputFilePath);
		if (FALSE == reader.Read()) {
			_tprintf(L"fail\n");
		} else {
			_tprintf(L"ok\n");
		}
		
	}

	return nRetCode;
}



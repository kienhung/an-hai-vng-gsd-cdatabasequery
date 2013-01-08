// LoopRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LoopRunner.h"
#include "..\AutoUpdate\MyPath.h"
typedef BOOL (*AutoDetectGameUpdate)(LPCTSTR strInput);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		CMyPath myPath;

		CString strExeFilePath = myPath.GetExeFilePath();
		CString strInputFilePath = strExeFilePath + L"\\input.ini";

		DWORD dwDelay = 4*60*60*1000;

		while(true)
		{
			HINSTANCE hLib = ::LoadLibrary(L"AutoUpdate");
			if (NULL != hLib)
			{
				AutoDetectGameUpdate detecter = (AutoDetectGameUpdate)GetProcAddress(hLib, "AutoDetectGameUpdate");
				if (NULL != detecter)
				{
					detecter(strInputFilePath);
				}
				::FreeLibrary(hLib);
			}
			printf("Tam dung %uh\n", dwDelay/(60*60*1000));
			::Sleep(dwDelay);
		}
		
		system("pause");
	}

	return nRetCode;
}

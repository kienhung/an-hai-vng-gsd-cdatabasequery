// AutoUpdateCF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutoUpdate.h"
#include "MyPath.h"
#include "InputReader.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

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



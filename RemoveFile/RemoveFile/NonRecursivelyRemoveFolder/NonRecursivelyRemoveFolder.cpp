// NonRecursivelyRemoveFolder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NonRecursivelyRemoveFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

#include <stack>

BOOL RemoveFolder (__in  LPCTSTR pstrPathName) {

	if (lstrlen(pstrPathName) + 1 > MAX_PATH) {
		return FALSE;
	}

	stack<TCHAR *> stackItems;
	stack<TCHAR *> stackDirectories;

	size_t uiLength = lstrlen(pstrPathName) + 1;
	TCHAR *ptc = new TCHAR[uiLength];

	_tcscpy_s(ptc, uiLength, pstrPathName);
	stackItems.push(ptc);

	

	return FALSE;
}

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
		// TODO: code your application's behavior here.
	}

	return nRetCode;
}

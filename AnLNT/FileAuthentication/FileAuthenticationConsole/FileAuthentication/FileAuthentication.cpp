// FileAuthentication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileAuthentication.h"
#include "FileSignature.h"
#include "FileUtility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

void TestSign();
void TestGetFileSize();

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
		TestSign();
		TestGetFileSize();
		printf("OK\n");
	}

	return nRetCode;
}

void TestSign() {

	CFileSignature fileSignature;
	ASSERT(fileSignature.Sign(L"D:\\abc.swf") == FALSE);
	//ASSERT(fileSignature.Sign(L"D:\\quangcao.swf") == TRUE);
	ASSERT(fileSignature.VerifySignature(L"D:\\quangcao.swf") == TRUE);

	ASSERT(fileSignature.Sign(L"D:\\quangcao2.swf") == TRUE);
	ASSERT(fileSignature.VerifySignature(L"D:\\quangcao2.swf") == TRUE);

	ASSERT(fileSignature.Sign(L"D:\\xxx.txt") == FALSE);
}

void TestGetFileSize() {

	CFileUtility fileUtility;

	CString strFileName = L"D:\\abc.txt";
	unsigned __int64 ui64FileSize;

	ASSERT(fileUtility.GetFileSize(strFileName, &ui64FileSize) == FALSE);

	strFileName = L"D:\\AnLNT\\Soft\\Installer\\Microsoft Visual Studio 2008\\Microsoft Visual Studio 2008 Pro Edition\\VS2008.iso";
	ASSERT(fileUtility.GetFileSize(strFileName, &ui64FileSize) == TRUE);
	ASSERT(3554287616 == ui64FileSize);

}
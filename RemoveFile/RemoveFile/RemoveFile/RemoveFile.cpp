// RemoveFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RemoveFile.h"

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
		//::RemoveDirectory(_T("D:\\Test\\."));
		::DeleteFile(_T("D:\\Test\\..\\abc.txt"));
		/*
		TCHAR szDir[MAX_PATH] = _T("D:\\Soft\\Demo\\*");
		WIN32_FIND_DATA ffd;
		LARGE_INTEGER filesize;
		HANDLE hFind = ::FindFirstFile(szDir, &ffd);

		if (INVALID_HANDLE_VALUE == hFind) {
			printf("FindFirstFile failed (%d)\n", GetLastError());
		}

		do {

			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				_tprintf(_T("%s<DIR>\n"), ffd.cFileName);
			} else {
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;
				_tprintf(_T("%s\n"), ffd.cFileName);
				//printf("         %s        %ld bytes\n",ffd.cFileName, filesize.QuadPart);
			}

		} while (FindNextFile(hFind, &ffd) != 0);

		printf("\n");
		int a = 5;
		*/
	}

	return nRetCode;
}

// readwriteunicodefile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "readwriteunicodefile.h"
#include "fstream"
#include <iostream>
#include "Strsafe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
void WriteToFile();
void ReadToFile();
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
		WriteToFile();

	}

	return nRetCode;
}
void WriteToFile()
{
	TCHAR strPath[MAX_PATH] = {0};

	GetCurrentDirectory(MAX_PATH, strPath);
	//StringCchCat(strPath, MAX_PATH, _T("\\danhsach.txt"));

	
	::GetModuleFileName(NULL, strPath, MAX_PATH);
	
	::PathRemoveFileSpec(strPath);
	::StrCat(strPath, _T("\\App.ini"));
	
	LPTSTR pszSectionB = _T("Hôm nay là thứ 5:"); // section name with bracket 
	LPTSTR pszSection = _T("\r\n\r\tNgày mai?"); // section name without bracket
	LPTSTR pszKey = _T("String");
	
	
	if(true)
	{
	
		// UTF16-LE BOM(FFFE)
		WORD wBOM = 0xFEFF;
		DWORD NumberOfBytesWritten;

		HANDLE hFile = ::CreateFile(strPath, GENERIC_WRITE, 0, 
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		::WriteFile(hFile, &wBOM, sizeof(WORD), &NumberOfBytesWritten, NULL);
		::WriteFile(hFile, pszSectionB, (_tcslen(pszSectionB)+1)*(sizeof(TCHAR) ), &NumberOfBytesWritten, NULL);
		::WriteFile(hFile, pszSection, ( _tcslen(pszSection))*(sizeof(TCHAR)), &NumberOfBytesWritten, NULL);	
		::CloseHandle(hFile);
	}
	
	//WritePrivateProfileString(pszSection, pszKey, _T("dfk"), strPath);
	
}

void ReadToFile()
{
	TCHAR strPath[MAX_PATH] = {0};

	GetCurrentDirectory(MAX_PATH, strPath);
	//StringCchCat(strPath, MAX_PATH, _T("\\danhsach.txt"));

	
	::GetModuleFileName(NULL, strPath, MAX_PATH);
	
	::PathRemoveFileSpec(strPath);
	::StrCat(strPath, _T("\\App.ini"));
	
	LPTSTR pszSectionB = _T("Tôi đi chơi"); // section name with bracket 
	LPTSTR pszSection = _T("StringTable"); // section name without bracket
	LPTSTR pszKey = _T("String");

	if(::PathFileExists(strPath))
	{
		
		
		DWORD NumberOfBytesWritten;

		HANDLE hFile = ::CreateFile(strPath, GENERIC_READ, 0, 
			NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		
		
		
		::CloseHandle(hFile);
	}
}
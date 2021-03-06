// convertutf8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "convertutf8.h"
#include "StringConverter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

//char* UnicodeToUtf8(LPCWSTR s);
//LPCWSTR Utf8ToUnicode(char* strUni);

LPCTSTR UTF8ToUnicode(char *pcStrIn) {

	LPTSTR ptcStrOut = NULL;

	if (NULL == pcStrIn) {
		return NULL;
	}

	int iLength = strlen(pcStrIn);

	if (0 == iLength ) {
		ptcStrOut = new TCHAR[1];
		ptcStrOut[0] = L'\0';
		return ptcStrOut;
	}

	int iSize = MultiByteToWideChar(CP_UTF8, 0, pcStrIn, iLength, NULL, 0);
	ptcStrOut = new TCHAR[iSize + 1];

	iSize = MultiByteToWideChar(CP_UTF8, 0, pcStrIn, iLength, ptcStrOut, iSize);

	if (iSize == 0) {
		delete[] ptcStrOut;
		return NULL;
	}

	ptcStrOut [iSize] = L'\0';

	return ptcStrOut;
}

char* UnicodeToUTF8(LPCTSTR ptcStrIn) {

	char *pcStrOut = NULL;

	if (ptcStrIn == NULL) {
		return NULL;
	}

	size_t uiLength = lstrlen(ptcStrIn);
	if (0 == uiLength) {
		pcStrOut = new char[1];
		pcStrOut[0] = '\0';
		return pcStrOut;
	}

	int iSize = WideCharToMultiByte(CP_UTF8, 0, ptcStrIn, uiLength, NULL, 0, NULL, NULL);
	if (0 == iSize) {
		return NULL;
	}

	pcStrOut = new char[iSize + 1];
	iSize = WideCharToMultiByte(CP_UTF8, 0, ptcStrIn, uiLength, pcStrOut, iSize, NULL, NULL);

	if (0 == iSize) 
	{
		delete[] pcStrOut;
		return NULL;
	}
	pcStrOut[iSize] = '\0';
	return pcStrOut;
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
		CStringConverter stringConverter;
		CStringConverter stringConverter2;

		TCHAR tstrHoTen[] = _T("Lê Nguyễn Thiện Ân");
		TCHAR tstrDiaChi[] = _T("3/4 Dạ Nam, Phường 2, Quận 8, Tp HCM");
		TCHAR tstrCongTy[] = _T("Tập đoàn công nghệ thông tin VNG");

		char *strHoTen = stringConverter.UnicodeToUTF8(tstrHoTen);
		LPCTSTR unicodeStrHoTen = stringConverter2.UTF8ToUnicode(strHoTen);

		char *strDiaChi = stringConverter.UnicodeToUTF8(tstrDiaChi);
		LPCTSTR unicodeStrDiaChi = stringConverter2.UTF8ToUnicode(strDiaChi);

		char *strCongTy = stringConverter.UnicodeToUTF8(tstrCongTy);		
		LPCTSTR unicodeStrCongTy = stringConverter.UTF8ToUnicode(strCongTy);

		//char *strUTF8 = stringConverter.UnicodeToUTF8(root);

		//CStringConverter stringConverter2;
		//LPCTSTR strUnicode = stringConverter.UTF8ToUnicode(strUTF8);

		int a = 10;
		// TODO: code your application's behavior here.
		//LPCWSTR root = _T("Cuộc tình xưa yêu dấu giờ là kỷ niệm buồn em đã xa tôi rồi");
		//char* kq = UnicodeToUtf8(root);
		//LPCWSTR temp = Utf8ToUnicode(kq);
		//cout<<temp;

	}

	return nRetCode;
}
/*
char* UnicodeToUtf8(LPCWSTR s)
{
	if (s == NULL) 
		return NULL;

	int iLength= lstrlenW(s);
	if (iLength==0) 
	{
		CHAR *psz = new CHAR[1];
		*psz = '\0';
		return psz;
	}
	int cc = WideCharToMultiByte(CP_UTF8, 0, s, iLength, NULL, 0, NULL, NULL);
	if (cc == 0) 
		return NULL;
	CHAR *psz=new CHAR[cc+1];
	cc = WideCharToMultiByte(CP_UTF8, 0, s, iLength, psz, cc, NULL, NULL);
	if (cc==0) 
	{
		delete[] psz;
		return NULL;
	}
	psz[cc]='\0';
	return psz;
}

LPCWSTR Utf8ToUnicode(char* strUni)
{
	if(strUni == NULL)
		return NULL;
	int iLength = strlen(strUni);
	if(iLength == 0)
	{
		WCHAR *pw = new WCHAR[1];
		*pw = L'\0';
		return pw;
	}
	
	int iSize_needed = MultiByteToWideChar(CP_UTF8, 0, strUni, iLength, NULL, 0);
	WCHAR* strKq = new WCHAR[iSize_needed + 1];
	iSize_needed = MultiByteToWideChar(CP_UTF8, 0, strUni, iLength, (LPWSTR)strKq, iSize_needed);
	strKq[iSize_needed] = L'\0';
	return strKq;
}
*/


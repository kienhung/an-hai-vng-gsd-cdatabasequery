#include "StdAfx.h"
#include "DuyetFile.h"
#include <windows.h>
#include "Strsafe.h"
#include "FileServices.h"

CDuyetFile::CDuyetFile(void)
{
	wmemset(strRootPath, 0, MAX_PATH);
}

CDuyetFile::~CDuyetFile(void)
{
}
void CDuyetFile::ClearList()
{
	
}

bool CDuyetFile::ApproveFolderToList(const TCHAR *strPath, const TCHAR* strFileName)
{
	CFileServices fileServices;
	if (fileServices.IsDirectory(strPath) == FALSE) {
		return false;
	}
	TCHAR strPathFileData[MAX_PATH] = {0};
	
	int iLength = wcslen(strPath);
	TCHAR strTempPath[MAX_PATH] = {0};
	
	StringCchPrintf(strTempPath, MAX_PATH, _T("%s\\*"), strPath);
	// UTF16-LE BOM(FFFE)
	WORD wBOM = 0xFEFF;
	DWORD NumberOfBytesWritten;

	HANDLE hFileOut = CreateFile(strFileName, FILE_WRITE_DATA, 0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE == hFileOut)
	{
		AfxMessageBox(_T("Không thể tạo file"), MB_ICONSTOP);
		return false;
	}
	//write unicode.
	::WriteFile(hFileOut, &wBOM, sizeof(WORD), &NumberOfBytesWritten, NULL);

	TCHAR strTemp[MAX_PATH] = {0};
	wmemset(strTemp, MAX_PATH, 0);
	StringCchCopy(strTemp, MAX_PATH, strPath);
	CString temp = strTempPath;
	temp.Delete(wcslen(temp) - 2, 2);
	int iIndex = (int)wcslen(temp);
	for(; iIndex >= 0 ; iIndex--)
	{
		if(temp[iIndex] == L'\\')
		{
			break;
		}
	}
	temp.Delete(iIndex + 1,(int)wcslen(temp) - iIndex +1 );
	//FormatPath(temp);
	StringCchCopy(strRootPath, MAX_PATH, temp);

	if(!ApproveFolder(strTempPath, &hFileOut))
	{
		AfxMessageBox(_T("Duyệt file thất bại"), MB_ICONSTOP);
	}

		
	CloseHandle(hFileOut);
	return true;
}
const TCHAR* CDuyetFile::FormatPath(const TCHAR *strPath)
{
	int iLengthPath = wcslen(strRootPath);
	const TCHAR* strTemp = strPath +iLengthPath;
	return strTemp;
	
}
bool CDuyetFile::ApproveFolder(const TCHAR *strPath, const HANDLE* hFile)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FindFileData;

	hFind = FindFirstFile(strPath, &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("Đường dẫn không hợp lệ"));
		return false;
	}

	while(FindNextFile(hFind, &FindFileData) != 0)
	{
		if(wcscmp(FindFileData.cFileName, _T(".")) != 0 && wcscmp(FindFileData.cFileName, _T("..")) != 0)
		{
			INFOFILE infoFile;
		
			TCHAR strFilePath[MAX_PATH];
			_tcscpy_s(strFilePath, strPath);
			int length = wcslen(strFilePath);
			strFilePath[length -1] = L'\0';
			wcscat_s(strFilePath, FindFileData.cFileName);

			_LARGE_INTEGER lInt;

			lInt.HighPart = FindFileData.ftLastWriteTime.dwHighDateTime;
			lInt.LowPart = FindFileData.ftLastWriteTime.dwLowDateTime;
			infoFile.llLastModified = lInt.QuadPart;

			infoFile.cTypeFile = 0;
			wcscpy_s(infoFile.strFileName, strFilePath);
			CString strTemp = infoFile.strFileName;
			
			
			
			lInt.HighPart = FindFileData.nFileSizeHigh;
			lInt.LowPart = FindFileData.nFileSizeLow;
			infoFile.llSize = lInt.QuadPart;

			if(GetFileAttributes(strFilePath) & FILE_ATTRIBUTE_DIRECTORY)
			{
				infoFile.cTypeFile = 1;
				WriteElementToFileText(infoFile, *hFile);
				wcscat_s(strFilePath,_T("\\*"));
				ApproveFolder(strFilePath, hFile);
			}
			else
			{
				WriteElementToFileText(infoFile, *hFile);
			}
		}
		
		
	}

	FindClose(hFind);
	return true;
}
void CDuyetFile::WriteElementToFile(const INFOFILE& infoFile,const HANDLE &hFile)
{
	DWORD dwPtr = SetFilePointer( hFile, 0, NULL, FILE_END);
	WriteFile(hFile, &infoFile, sizeof(INFOFILE), &dwPtr, NULL);
}


void CDuyetFile::WriteElementToFileText(const INFOFILE& infoFile, const HANDLE &hFile)
{
	DWORD dwPtr = SetFilePointer( hFile, 0, NULL, FILE_END);
	
	TCHAR strTemp[MAX_PATH] = {0};
	
	
	const TCHAR* strPath = FormatPath(infoFile.strFileName);
	
	//Write file name.
	StringCchPrintf(strTemp, MAX_PATH, _T("%s%s"),strPath, _T("\r\n") );
	WriteFile(hFile, strTemp, wcslen(strTemp) * sizeof(TCHAR), &dwPtr, NULL);

	//Write type file.
	wmemset(strTemp, 0, MAX_PATH);
	StringCchPrintf(strTemp, MAX_PATH, _T("\r\t%d\r\n"), infoFile.cTypeFile);
	WriteFile(hFile, strTemp, wcslen(strTemp) * sizeof(TCHAR), &dwPtr, NULL);

	//Write file size.
	wmemset(strTemp, 0, MAX_PATH);
	StringCchPrintf(strTemp, MAX_PATH, _T("\r\t%I64u\r\n"), infoFile.llSize);
	WriteFile(hFile, strTemp, wcslen(strTemp) * sizeof(TCHAR), &dwPtr, NULL);
	
	//Write last modified.
	wmemset(strTemp, 0, MAX_PATH);
	StringCchPrintf(strTemp, MAX_PATH, _T("\r\t%I64u\r\n"), infoFile.llLastModified);
	WriteFile(hFile, strTemp, wcslen(strTemp) * sizeof(TCHAR), &dwPtr, NULL);
}

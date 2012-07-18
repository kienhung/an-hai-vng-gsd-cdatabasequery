#include "StdAfx.h"
#include "DuyetFile.h"
#include <windows.h>
#include "Strsafe.h"

CDuyetFile::CDuyetFile(void)
{
}

CDuyetFile::~CDuyetFile(void)
{
}
void CDuyetFile::ClearList()
{
	lstFile.clear();
}
void CDuyetFile::ApproveFolderToList(const TCHAR *strPath)
{
	ClearList();
	if(ApproveFolder(strPath))
	{
		AfxMessageBox(_T("Duyệt file hoàn tất"), MB_ICONINFORMATION);
	}
	else
		AfxMessageBox(_T("Duyệt file thất bại"), MB_ICONSTOP);
}
bool CDuyetFile::ApproveFolder(const TCHAR *strPath)
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
			
			infoFile.cTypeFile = 0;
			wcscpy_s(infoFile.strFileName, strFilePath);
			infoFile.llLastModified = lInt.QuadPart;
			
			lInt.HighPart = FindFileData.nFileSizeHigh;
			lInt.LowPart = FindFileData.nFileSizeLow;
			infoFile.llSize = lInt.QuadPart;

			if(GetFileAttributes(strFilePath) == FILE_ATTRIBUTE_DIRECTORY)
			{
				infoFile.cTypeFile = 1;
				lstFile.push_back(infoFile);
				wcscat_s(strFilePath,_T("\\*"));
				ApproveFolder(strFilePath);
			}
			else
				lstFile.push_back(infoFile);
		}
		
		
	}

	FindClose(hFind);
	return true;
}

void CDuyetFile::WriteToFile()
{
	if(lstFile.empty())
	{
		AfxMessageBox(_T("Bạn chưa duyệt file"), MB_ICONSTOP);
		return;
	}
	TCHAR strPath[MAX_PATH] = {0};

	GetCurrentDirectory(MAX_PATH, strPath);
	StringCchCat(strPath, MAX_PATH, _T("\\danhsach.txt"));
	
	HANDLE hOut = CreateFile(strPath, FILE_WRITE_DATA, 0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE == hOut)
	{
		AfxMessageBox(_T("Không thể tạo file"), MB_ICONSTOP);
		return;
	}
	while(lstFile.size() > 0)
	{
		INFOFILE infoFile = (INFOFILE)lstFile.front();
		WriteElementToFile(infoFile, hOut);
		lstFile.erase(lstFile.begin(),lstFile.begin() +1);
	}	
	CloseHandle(hOut);
	AfxMessageBox(_T("Ghi danh sách ra file hoàn tất"), MB_ICONINFORMATION);
		
}
void CDuyetFile::WriteElementToFile(const INFOFILE& infoFile,const HANDLE &hFile)
{
	DWORD dwPtr = SetFilePointer( hFile, 0, NULL, FILE_END);
	WriteFile(hFile, &infoFile, sizeof(INFOFILE), &dwPtr, NULL);
}
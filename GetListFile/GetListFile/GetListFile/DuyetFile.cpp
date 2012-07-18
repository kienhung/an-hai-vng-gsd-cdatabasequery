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
		TCHAR strTemp[MAX_PATH] = {0};
		StringCchCopy(strTemp, MAX_PATH, strPath);
		CString temp = strPath;
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
		FormatPath(temp);
		AfxMessageBox(_T("Duyệt file hoàn tất"), MB_ICONINFORMATION);
	}
	else
		AfxMessageBox(_T("Duyệt file thất bại"), MB_ICONSTOP);
	
}
void CDuyetFile::FormatPath(const TCHAR *strPath)
{
	int iLengthPath = wcslen(strPath);
	for(int i = 0; i < (int)lstFile.size(); i++)
	{
		CString strTemp = lstFile[i].strFileName;
		strTemp.Delete(0, iLengthPath);
		wmemset(lstFile[i].strFileName, L'\0', MAX_PATH);
		StringCchCopy(lstFile[i].strFileName, MAX_PATH, strTemp);
	}
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
			infoFile.llLastModified = lInt.QuadPart;

			infoFile.cTypeFile = 0;
			wcscpy_s(infoFile.strFileName, strFilePath);
			CString strTemp = infoFile.strFileName;
			
			
			
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

void CDuyetFile::WriteToFileText()
{
	if(lstFile.empty())
	{
		AfxMessageBox(_T("Bạn chưa duyệt file"), MB_ICONSTOP);
		return;
	}
	TCHAR strPath[MAX_PATH] = {0};

	GetCurrentDirectory(MAX_PATH, strPath);
	StringCchCat(strPath, MAX_PATH, _T("\\danhsach.txt"));
	
	FILE *pFile = new FILE();
	

	_wfopen_s(&pFile, strPath, _T("w+| ccs=UNICODE"));
	
	//::File* pFile = new File();
	//TStringList *list = new TStringList;
}

void CDuyetFile::WriteElementToFileText(const INFOFILE& infoFile, const HANDLE &hFile)
{

}

vector<INFOFILE> CDuyetFile::ReadFileToList(const TCHAR* strPath)
{
	vector<INFOFILE> lstFilesToDownload;
	HANDLE hFile = CreateFileW(strPath, FILE_READ_DATA, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("Không tìm thấy file."));
		return lstFilesToDownload;
	}
	DWORD size;
	do
	{
		INFOFILE infoFile;
		ReadFile(hFile, &infoFile, sizeof(INFOFILE), &size, NULL);
		lstFilesToDownload.push_back(infoFile);
	}while(size > 0);
	lstFilesToDownload.pop_back();
	return lstFilesToDownload;
}
vector<INFOFILE> CDuyetFile::ReadTextFileToList(const TCHAR* strPath)
{
	vector<INFOFILE> lstFilesToDownload;
	return lstFilesToDownload;
}

vector<INFOFILE> CDuyetFile::CheckListFile(const TCHAR* strPath)
{
	vector<INFOFILE> lstDownload = GetListFileToDownload(strPath);
	return lstDownload;
}


vector<INFOFILE> CDuyetFile::GetListFileToDownload(const TCHAR* strPath)
{
	vector<INFOFILE> lstDownload;
	TCHAR strFilePath[MAX_PATH] = {0};

	GetCurrentDirectory(MAX_PATH, strFilePath);
	StringCchCat(strFilePath, MAX_PATH, _T("\\danhsach.txt"));

	vector<INFOFILE> lstToDownloadFromServer = ReadFileToList(strFilePath);

	ApproveFolderToList(strPath);
	
	for(int i = 0 ; i < (int)lstToDownloadFromServer.size(); i++)
	{
		bool flag = true;
		for(int j = 0; j < (int)lstFile.size(); j++)
		{
			if(CompareTwoInfoFile(&lstToDownloadFromServer[i], &lstFile[j]))
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			INFOFILE infoFile = lstToDownloadFromServer[i];
			lstDownload.push_back(infoFile);
		}
	}
	return lstDownload;
}
bool CDuyetFile::CompareTwoInfoFile(const INFOFILE* infoFileDest, const INFOFILE* infoFileSource)
{
	if(wcscmp(infoFileDest->strFileName, infoFileSource->strFileName) != 0)
		return false;
	if(infoFileDest->cTypeFile != infoFileSource->cTypeFile)
		return false;
	if(infoFileDest->llSize != infoFileSource->llSize)
		return false;
	if(infoFileDest->llLastModified != infoFileSource->llLastModified)
		return false;
	return true;
}
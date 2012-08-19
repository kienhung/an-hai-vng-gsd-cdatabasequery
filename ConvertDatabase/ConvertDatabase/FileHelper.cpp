#pragma once
#include "StdAfx.h"
#include "FileHelper.h"
#include "Strsafe.h"

CFileHelper::CFileHelper(void)
{
}

CFileHelper::~CFileHelper(void)
{
}

BOOL CFileHelper::CopyFolder(const TCHAR *strSourceDir, const TCHAR *strDestDir)
{
	CString strTempSourceDir(strSourceDir);
	
	strTempSourceDir.Delete(0, strTempSourceDir.ReverseFind(L'\\') +1);
	TCHAR strTempDestDir[MAX_PATH] = {0};
	StringCchPrintf(strTempDestDir, MAX_PATH, _T("%s\\%s"), strDestDir, strTempSourceDir);
	CreateDirectory(strTempDestDir, NULL);
	return CopyFolderProcess(strSourceDir, strTempDestDir);
}
BOOL CFileHelper::CopyAndRenameFolder(const TCHAR* strSourceDir, const TCHAR* strDestDir, const TCHAR* strNewFolderName)
{
	/*CString strTempSourceDir(strSourceDir);
	
	strTempSourceDir.Delete(0, strTempSourceDir.ReverseFind(L'\\') +1);*/
	TCHAR strTempDestDir[MAX_PATH] = {0};
	StringCchPrintf(strTempDestDir, MAX_PATH, _T("%s\\%s"), strDestDir, strNewFolderName);

	CreateDirectory(strTempDestDir, NULL);

	return CopyFolderProcess(strSourceDir, strTempDestDir);
}

BOOL CFileHelper::CopyFolderProcess(const TCHAR *strSourceDir, const TCHAR *strDestDir)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR strTemp[MAX_PATH] = {0};

	StringCchPrintf(strTemp, MAX_PATH, _T("%s\\*"), strSourceDir);

	TCHAR strTempSourceDir[MAX_PATH] = {0};
	TCHAR strTempDestDir[MAX_PATH] = {0};
	StringCchPrintf(strTempSourceDir, MAX_PATH, _T("%s\\"), strSourceDir);
	StringCchPrintf(strTempDestDir, MAX_PATH, _T("%s\\"), strDestDir);

	TCHAR strNewSrcPath[MAX_PATH] = {0};
	TCHAR strNewDesPath[MAX_PATH] = {0};

	hFind = FindFirstFile(strTemp, &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE)
	  return FALSE;
	
	do
	{
	  if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	  {
		  if(wcscmp(FindFileData.cFileName,_T(".")))
		  {
			  if(wcscmp(FindFileData.cFileName,_T("..")))
			  {
				  StringCchPrintf(strNewSrcPath, MAX_PATH, _T("%s\\%s"),strTempSourceDir, FindFileData.cFileName );
				  StringCchPrintf(strNewDesPath, MAX_PATH, _T("%s\\%s"),strTempDestDir, FindFileData.cFileName );
				  CreateDirectory(strNewDesPath,NULL);
				  CopyFolderProcess(strNewSrcPath,strNewDesPath);
			  }
		  }
	  }
	  else
	  {
		  TCHAR strSourcFile[MAX_PATH] = {0};
		  TCHAR strDestFile[MAX_PATH] = {0};

		  StringCchPrintf(strSourcFile, MAX_PATH, _T("%s\\%s"),strTempSourceDir, FindFileData.cFileName );
		  StringCchPrintf(strDestFile, MAX_PATH, _T("%s\\%s"),strTempDestDir, FindFileData.cFileName );
		  
		  BOOL l_bRet = CopyFile(strSourcFile,strDestFile,TRUE);
	  }
	}while(FindNextFile(hFind, &FindFileData));

	FindClose(hFind);
	return TRUE;
}

BOOL CFileHelper::DeleteFolder(const TCHAR* strDirPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR strTemp[MAX_PATH] = {0};

	StringCchPrintf(strTemp, MAX_PATH, _T("%s\\*"), strDirPath);

	TCHAR strNewPath[MAX_PATH] = {0};

	hFind = FindFirstFile(strTemp, &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE)
	  return FALSE;
	
	do
	{
		StringCchPrintf(strNewPath, MAX_PATH, _T("%s\\%s"),strDirPath, FindFileData.cFileName );
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		{
			DWORD attr = GetFileAttributes(strNewPath);
			attr &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes(strNewPath, attr );
		}

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(wcscmp(FindFileData.cFileName,_T(".")))
			{
				if(wcscmp(FindFileData.cFileName,_T("..")))
				{	
					DeleteFolder(strNewPath);
					RemoveDirectory(strNewPath);
				}
			}
		}
		else
		{
			DeleteFile(strNewPath);
		}
	}while(FindNextFile(hFind, &FindFileData));

	FindClose(hFind);
	RemoveDirectory(strDirPath);
	return TRUE;
}
#include "StdAfx.h"
#include "MailProjectUtility.h"
#include "MyUtils.h"

CMailProjectUtility::CMailProjectUtility(void)
{
}

CMailProjectUtility::~CMailProjectUtility(void)
{
}

vector<string> CMailProjectUtility::GetListGameForMail( LPCTSTR strFileName )
{
	vector <string> vGames;
	vGames.reserve(NUM_GAMES);

	CStringArray listGames;
	CMyUtils::ReadINISectionNames(strFileName, listGames);

	int iCount = listGames.GetCount();

	for (int i = 0; i < iCount; i++)
	{
		UINT uiValue = GetPrivateProfileInt(listGames[i], L"mail", 0, strFileName);
		if (1 == uiValue)
		{
			char* utf8Alias = CMyUtils::ConvertWideCharToUTF8(listGames[i]);
			if (NULL != utf8Alias)
			{
				vGames.push_back(utf8Alias);
				delete[] utf8Alias;
			}
		}
	}

	return vGames;
}

bool CMailProjectUtility::CheckGameHasUpdate( string sAlias, LPCTSTR strReportFolder )
{
	TCHAR * strUnicodeAlias = CMyUtils::ConvertUTF8ToWideChar(sAlias.c_str());
	bool bReturn = false;

	if (strUnicodeAlias != NULL)
	{
		CString strFullFileName;
		strFullFileName.Format(L"%s\\%s.txt", strReportFolder, strUnicodeAlias);

		WIN32_FIND_DATA findData;
		ZeroMemory(&findData, sizeof(WIN32_FIND_DATA));

		HANDLE hFind = FindFirstFile(strFullFileName, &findData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			bReturn = true;
			FindClose(hFind);
		}
		
		delete[] strUnicodeAlias;
	}
	return bReturn;
}

vector<pair<string,int>> CMailProjectUtility::PrepareListGameForXml( const vector<string> &vGames, LPCTSTR strReportFolder )
{
	vector<pair<string, int>> vResult;
	vResult.reserve(NUM_GAMES);

	for (int i = 0; i < vGames.size(); i++)
	{
		int iGameUpdate = 0;
		if (CMailProjectUtility::CheckGameHasUpdate(vGames[i], strReportFolder) == true)
		{
			iGameUpdate = 1;
		}
		pair<string, int> game(vGames[i], iGameUpdate);
		vResult.push_back(game);
	}
	return vResult;
}

BOOL CMailProjectUtility::GetModifyTime( LPCTSTR strFileName, FILETIME &fileTime )
{
	HANDLE hFile;

	hFile = CreateFile(     strFileName, 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
		return FALSE;

	if (!GetFileTime(hFile, NULL, NULL, &fileTime))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	CloseHandle(hFile);

	return TRUE;
}


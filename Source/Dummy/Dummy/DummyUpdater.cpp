#include "StdAfx.h"
#include "DummyUpdater.h"
#include "Utility/MyUtility.h"
#include "Resource.h"
#include "WinINET/HTTPDownloader.h"
#include <fstream>
#include <string>
#include "Utility/PathUtility.h"
#include "Utility/FolderDeleter.h"
#include "Dummy.h"


using namespace std;

CDummyUpdater::CDummyUpdater(void)
{
}

CDummyUpdater::~CDummyUpdater(void)
{
}

BOOL CDummyUpdater::IsNeedUpdate()
{
	if (FALSE == DeleteTempFolder())
	{
		return FALSE;
	}

	CString cstrTempFilePath;
	if (FALSE == CMyUtility::CreateTempFilePath(cstrTempFilePath))
	{
		return FALSE;
	}

	BOOL bResult = TRUE;

	try 
	{
		CHTTPDownloader httpDownloader;

		if (FALSE == httpDownloader.Download(URL_VERSION, cstrTempFilePath))
		{
			throw L"To Download dmver.dat is failed";
		}

		ifstream versionFileReader (cstrTempFilePath, ios::in);
		if (false == versionFileReader.is_open())
		{
			throw L"To Open dmver.dat is failed";
		}

		string strLine = "unknown";
		getline(versionFileReader, strLine);
		versionFileReader.close();

		CStringA strAppVersion;
		strAppVersion.LoadString(IDS_APP_VERSION);

		if (strLine.compare("unknown") == 0)
		{
			bResult = false;
		}
		else
		{
			bResult = (strAppVersion != strLine.c_str());
		}

	} 
	catch (LPCTSTR strErrorMessage)
	{
		bResult = FALSE;

		CString strTextFormater;
		strTextFormater.Format(L"Error: %s with error code %u\n", strErrorMessage, GetLastError());
		::OutputDebugString(strTextFormater);
	}

	DeleteFile(cstrTempFilePath);
	return bResult;

}

BOOL CDummyUpdater::StartUpdate()
{
	CString cstrTempFolderPath = CPathUtility::GetExeDirectory() + L"\\Temp";
	if (FALSE == ::CreateDirectory(cstrTempFolderPath, NULL))
	{
		return FALSE;
	}

	CString cstrUpdatePackageFilePath = cstrTempFolderPath+ L"\\dmup.zip";

	BOOL bResult = TRUE;

	try 
	{
		CHTTPDownloader httpDownloader;

		if (FALSE == httpDownloader.Download(URL_UPDATE_PACKAGE,  cstrUpdatePackageFilePath))
		{
			throw L"To Download dmver.dat is failed";
		}
		
		if (FALSE == CMyUtility::UnZip(cstrUpdatePackageFilePath, NULL, cstrTempFolderPath))
		{
			throw L"TO extract update package is failed";
		}

		CString strDummyLauncherPath = cstrTempFolderPath + L"\\DummyLaucher.exe";
		StartProcessDummyLaucher(strDummyLauncherPath);

	} 
	catch (LPCTSTR strErrorMessage)
	{
		bResult = FALSE;

		CString strTextFormater;
		strTextFormater.Format(L"Error: %s with error code %u\n", strErrorMessage, GetLastError());
		::OutputDebugString(strTextFormater);
	}

	return bResult;
}

BOOL CDummyUpdater::DeleteTempFolder()
{
	
	CString cstrTempFolderPath = theApp.GetExeDirectory() + L"\\Temp";
	
	if (CPathUtility::IsPathDirectory(cstrTempFolderPath))
	{
		CFolderDeleter folderDeleter;
		return folderDeleter.Delete(cstrTempFolderPath);
		
	}
	

	return TRUE;
}

void CDummyUpdater::StartProcessDummyLaucher( const TCHAR* strPathLaucher )
{
	BOOL bWorked;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	CString m_Process(strPathLaucher);

	TCHAR strCommdline[MAX_PATH] = {0};
	GetModuleFileName(NULL, strCommdline, MAX_PATH);

	CString strClassName;

	strClassName.LoadString(IDS_APP_CLASS_NAME);
	swprintf(strCommdline, MAX_PATH, _T("%s@%s"), strCommdline, strClassName.GetBuffer());
	//_stprintf(strCommdline + _tcslen(strCommdline), _T("@%s"), strClassName.GetBuffer());

	bWorked = ::CreateProcess(m_Process,strCommdline,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);
}

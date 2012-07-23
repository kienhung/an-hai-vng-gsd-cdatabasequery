#pragma once
#include "vector"
#include "ClientDlg.h"
using namespace std;

typedef struct INFOFILE
{
	TCHAR strFileName[MAX_PATH];
	BYTE cTypeFile;
	LONGLONG llSize;
	LONGLONG llLastModified;
}INFOFILE;

class CDuyetFile
{
private:

	TCHAR strRootPath[MAX_PATH];
	
public:
	CDuyetFile(void);
	~CDuyetFile(void);
	void ClearList();
	const TCHAR* FormatPath(const TCHAR *strPath);
	bool ApproveFolder(const TCHAR *strPath,const HANDLE *hFile);
	void ApproveFolderToList(const TCHAR *strPath);
	
	
	void WriteElementToFileText(const INFOFILE& infoFile, const HANDLE &hFile);
	
	void ApproveFolderToDownload(CClientDlg *pClientDlg, const TCHAR *strRootPath, const TCHAR* strFullPathBuild);
	bool CompareTwoInfoFile(const INFOFILE* infoFileDest, const INFOFILE* infoFileSource);
	bool CompareTwoInfoFIle(const INFOFILE* infoFile);

};

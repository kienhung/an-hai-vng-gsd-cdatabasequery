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
	vector<INFOFILE> lstFile;
	TCHAR strRootPath[MAX_PATH];
public:
	CDuyetFile(void);
	~CDuyetFile(void);
	void ClearList();
	const TCHAR* FormatPath(const TCHAR *strPath);
	bool ApproveFolder(const TCHAR *strPath,const HANDLE *hFile);
	void ApproveFolderToList(const TCHAR *strPath);
	void WriteToFile();
	void WriteElementToFile(const INFOFILE& infoFile, const HANDLE &hFile);

	void WriteToFileText();
	void WriteElementToFileText(const INFOFILE& infoFile, const HANDLE &hFile);
	
	/*vector<INFOFILE> ReadFileToList(const TCHAR* strPath);
	vector<INFOFILE> ReadTextFileToList(const TCHAR* strPath);

	vector<INFOFILE> GetListFileToDownload(const TCHAR* strPath);vector<INFOFILE> CheckListFile(const TCHAR* strPath);*/
	void ApproveFolderToDownload(CClientDlg *pClientDlg, const TCHAR *strRootPath, const TCHAR* strFullPathBuild);
	bool CompareTwoInfoFile(const INFOFILE* infoFileDest, const INFOFILE* infoFileSource);
	bool CompareTwoInfoFIle(const INFOFILE* infoFile);

};

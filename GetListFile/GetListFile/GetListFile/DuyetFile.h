#pragma once
#include "vector"
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
public:
	CDuyetFile(void);
	~CDuyetFile(void);
	void ClearList();
	void FormatPath(const TCHAR *strPath);
	bool ApproveFolder(const TCHAR *strPath);
	void ApproveFolderToList(const TCHAR *strPath);
	void WriteToFile();
	void WriteElementToFile(const INFOFILE& infoFile, const HANDLE &hFile);

	void WriteToFileText();
	void WriteElementToFileText(const INFOFILE& infoFile, const HANDLE &hFile);
	
	vector<INFOFILE> ReadFileToList(const TCHAR* strPath);
	vector<INFOFILE> ReadTextFileToList(const TCHAR* strPath);

	vector<INFOFILE> GetListFileToDownload(const TCHAR* strPath);
	bool CompareTwoInfoFile(const INFOFILE* infoFileDest, const INFOFILE* infoFileSource);
	vector<INFOFILE> CheckListFile(const TCHAR* strPath);
};

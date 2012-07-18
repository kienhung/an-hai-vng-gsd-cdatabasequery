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
	bool ApproveFolder(const TCHAR *strPath);
	void ApproveFolderToList(const TCHAR *strPath);
	void WriteToFile();
	void WriteElementToFile(const INFOFILE& infoFile, const HANDLE &hFile);
};

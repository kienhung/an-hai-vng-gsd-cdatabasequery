#pragma once
#include "vector"
using namespace std;

typedef struct INFOFILE
{
	TCHAR strFileName[MAX_PATH];
	BYTE cTypeFile;
	DWORD ulSize;
	ULONGLONG ullLastModified;
}INFOFILE;

class CDuyetFile
{
private:
	vector<INFOFILE> lstFile;
public:
	CDuyetFile(void);
	~CDuyetFile(void);

	void ApproveFolder(const TCHAR *strPath);
};

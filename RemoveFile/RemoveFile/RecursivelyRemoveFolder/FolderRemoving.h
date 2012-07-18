#pragma once
#include <stack>

using namespace std;

class CFolderRemoving
{

protected:
public:

	CFolderRemoving(void);
	~CFolderRemoving(void);

	BOOL IsDirectory(const TCHAR strPath[]);
	BOOL RemoveFile(const TCHAR strPath[]);
	BOOL RemoveFolder(const TCHAR strPath[]);

	//BOOL IsFile(const TCHAR strPath[]);
};

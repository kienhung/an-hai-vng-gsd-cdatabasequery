#pragma once
#include <stack>

using namespace std;

class CFolderRemoving
{
protected:

	stack<TCHAR *> m_stackItems;
	stack<TCHAR *> m_stackDirectories;

	void AddChildsToItemsStack(const TCHAR strPath[]);

public:

	CFolderRemoving(void);
	~CFolderRemoving(void);

	BOOL IsDirectory(const TCHAR strPath[]);
	BOOL IsFile(const TCHAR strPath[]);

	BOOL NonRecursivelyRemove(const TCHAR strPath[]);
};

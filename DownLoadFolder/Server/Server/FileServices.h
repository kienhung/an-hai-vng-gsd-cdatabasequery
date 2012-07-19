#pragma once

class CFileServices
{
public:
	CFileServices(void);
	~CFileServices(void);
	unsigned __int64 GetFileSize(HANDLE hFile);
};

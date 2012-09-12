#pragma once
#include "BlackListDAO.h"

class CBlackListReader
{
public:
	CBlackListReader(void);
	~CBlackListReader(void);
	BOOL Read(LPCTSTR strFilePath);

protected:
	BOOL ProcessURL(const char* strURL);

protected:
	CBlackListDAO m_blackListDAO;
	BOOL m_bIsConnected;
};

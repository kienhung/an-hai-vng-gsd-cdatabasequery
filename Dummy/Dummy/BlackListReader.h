#pragma once

class CBlackListReader
{
public:
	CBlackListReader(void);
	~CBlackListReader(void);
	BOOL Read(LPCTSTR strFilePath);
protected:
	BOOL ProcessItem(LPCTSTR strItemText);
};

#pragma once

class CMyUtility
{
public:
	CMyUtility(void);
	virtual ~CMyUtility(void);

	static BOOL UnZip(LPCTSTR wcPathIn, LPCTSTR wcExtractObject, LPCTSTR wcPathOut);
};

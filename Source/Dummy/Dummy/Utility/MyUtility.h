#pragma once
#include <string>
using namespace std;

class CMyUtility
{
public:
	CMyUtility(void);
	virtual ~CMyUtility(void);

	static BOOL UnZip(LPCTSTR wcPathIn, LPCTSTR wcExtractObject, LPCTSTR wcPathOut);
	static BOOL CreateTempFilePath(CString &cstrOut);
	static BOOL GetModifyTime(LPCTSTR strFileName, FILETIME &fileTime);
	static BOOL QueryMasterModifyTime(LPCTSTR strMasterFile, SYSTEMTIME *lpSysTime);
	static BOOL SetModifyTime(LPCTSTR strFileName, const FILETIME &modifyTime);
	static BOOL CheckFileExist( LPCTSTR strFilePath );
	static BOOL Decode(LPCTSTR strSource, LPCTSTR strDest);
	static void StringTrim(string &str);
	static CString GetIPGateway();
};

#pragma once

class CMyUtils
{
public:
	CMyUtils(void);
	~CMyUtils(void);
	static CString GetLicenseID();
	static BOOL CheckMacAddressValid(const TCHAR* strMacAdd, const TCHAR* strHwSerial, const CString& strLcID, CString& strMC);
	static CString GetMachineCode();
	static VARIANT CreateVariantPostData(const CString &strPost);

	static BOOL ConvertStringToSystemTime(SYSTEMTIME& systemTime, const CString& strTime);
	
};

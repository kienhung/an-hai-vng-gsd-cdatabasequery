#pragma once

class CMyUtils
{
public:
	CMyUtils(void);
	~CMyUtils(void);
	static CString GetLicenseID();
	static BOOL CheckMacAddressValid(const TCHAR* strMacAdd, const TCHAR* strHwSerial, CString strLcID, CString& strMC);
	static CString GetMachineCode();
};

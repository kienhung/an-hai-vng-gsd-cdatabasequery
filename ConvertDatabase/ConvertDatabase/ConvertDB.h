#pragma once
#include <afxcmn.h>
#include <afxdb.h>
#include "MyStruct.h"



class CConvertDB
{
protected:
	CONNECTSTRINGTOMYSQL m_ConnectStringToMYSQL;
	
public:
	CConvertDB(void);
	~CConvertDB(void);

	virtual BOOL Connect(const TCHAR* strPath) = 0;
	virtual BOOL Convert(const TCHAR* strPath) = 0;
	VOID VariantToCstring(const CDBVariant &var, CString &sData);

	virtual BOOL ConvertBlackList() = 0;
	virtual BOOL ConvertUser() = 0;
	virtual BOOL ConvertService() = 0;
	
};

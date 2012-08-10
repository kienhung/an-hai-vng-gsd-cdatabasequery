#pragma once
#include "ConvertDB.h"
class CAccessConvertDB: public CConvertDB
{
private:
	CDatabase m_db;
public:
	CAccessConvertDB(void);
	~CAccessConvertDB(void);
	virtual BOOL Convert(const TCHAR* strPath);
	virtual BOOL Connect(const TCHAR* strPath);
	BOOL ConvertBlackList();
	BOOL ConvertUser();
	BOOL ConvertService();
};

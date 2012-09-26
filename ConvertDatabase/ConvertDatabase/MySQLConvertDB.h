#pragma warning(disable :4995 )
#pragma once
#include <vector>
#include "MySQLDataAccessHelper.h"
#include "MyStruct.h"
#include "ConvertDB.h"
using namespace std;


class CMySQLConvertDB: public CConvertDB
{
private:
	CONNECTSTRINGTOMYSQL  m_ConnectStringToMYSQLOneNet;
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
	CString m_DataDirName;
public:
	CMySQLConvertDB(void);
	~CMySQLConvertDB(void);
	void InitConnectString();
	virtual BOOL Convert(const TCHAR* strPath);
	virtual BOOL Connect(const TCHAR* strPath);
	
	virtual BOOL ConvertBlackList();
	virtual BOOL ConvertUser();
	virtual BOOL ConvertService();
	BOOL ConvertWebHistory();

	BOOL CheckPathInDataMySQL(const TCHAR* strPathDirectory);
	
	BOOL CopyDataToDataMySQL(const TCHAR* strPathDirectory);
	BOOL DeleteDataCopy(const TCHAR* strPathDirectory);

};

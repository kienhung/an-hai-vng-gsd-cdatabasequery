#pragma once
#include "phongbandao.h"
#include "MySQLDataAccessHelper.h"

class CMySqlPhongBanDAO :
	public CPhongBanDAO
{
protected:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
public:
	CMySqlPhongBanDAO(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	virtual size_t GetAll(list<PHONGBAN> *plstPhongBan);
	virtual ~CMySqlPhongBanDAO(void);
};

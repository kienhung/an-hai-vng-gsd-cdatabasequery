#include "StdAfx.h"
#include "MySqlPhongBanDAO.h"
#include "MyException.h"
#include "StringConverter.h"

CMySqlPhongBanDAO::CMySqlPhongBanDAO(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase)
{
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(pcUserName, pcPassword, pcServerAddress, pcDatabase);
}

CMySqlPhongBanDAO::~CMySqlPhongBanDAO(void)
{
	if (m_pSQLDataAccessHelper != NULL) {
		delete m_pSQLDataAccessHelper ;
	}
}

size_t CMySqlPhongBanDAO::GetAll(list<PHONGBAN> *plstPhongBan) {

	if (NULL == plstPhongBan) {
		throw new CMyException("NULL Pointer", NULL_POINTER);
	}
	plstPhongBan->clear();

	MYSQL_RES *pMySQLQueryResult = m_pSQLDataAccessHelper->ExecuteQuery("SELECT * FROM PHONGBAN");
	int iNumFields = mysql_num_fields(pMySQLQueryResult);

	int MAX_NUM_FIELDS = 2;
	CStringConverter stringConverter;

	if (MAX_NUM_FIELDS == iNumFields) {

		MYSQL_ROW mySQLResultRow;

		while ((mySQLResultRow = mysql_fetch_row(pMySQLQueryResult))) {

			PHONGBAN phongBan;
			phongBan.iMaPhongBan = atoi(mySQLResultRow[0]);

			const TCHAR *ptcTenPhongBan = stringConverter.UTF8ToUnicode(mySQLResultRow[1]);
			_tcscpy_s(phongBan.strTenPhongBan, MAX_NAME + 1, ptcTenPhongBan);

			plstPhongBan->push_back(phongBan);
		}
	}
	
	m_pSQLDataAccessHelper->FreeQueryResult(pMySQLQueryResult);
	return plstPhongBan->size();
}

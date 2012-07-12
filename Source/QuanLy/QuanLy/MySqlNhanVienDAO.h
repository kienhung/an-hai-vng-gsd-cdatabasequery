#pragma once
#include "nhanviendao.h"
#include "SimpleDAO.h"

class CMySqlNhanVienDAO :
	public CNhanVienDAO
{
protected:
	CMySQLDataAccessHelper *m_pSQLDataAccessHelper;
public:
	CMySqlNhanVienDAO(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	virtual ~CMySqlNhanVienDAO(void);

	virtual size_t GetAll(list<NHANVIEN> *plstNhanVien);
	virtual bool AddNhanVien(const NHANVIEN &nhanVien, int iMaPhongBan);
	virtual bool UpdateNhanVien(const NHANVIEN &nhanVien, int iMaPhongBan);
	virtual bool DeleteNhanVien(int iMaNhanVien);
};

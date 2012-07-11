#pragma once
#include "nhanviendao.h"

class CMySqlNhanVienDAO :
	public CNhanVienDAO
{
public:
	CMySqlNhanVienDAO(char *pcUserName, char *pcPassword, char *pcServerAddress, char *pcDatabase);
	~CMySqlNhanVienDAO(void);

	virtual size_t GetAll(list<NHANVIEN> *plstNhanVien);
	virtual bool AddNhanVien(const NHANVIEN &nhanVien);
	virtual bool UpdateNhanVien(const NHANVIEN &nhanVien);
	virtual bool DeleteNhanVien(int iMaNhanVien);
};

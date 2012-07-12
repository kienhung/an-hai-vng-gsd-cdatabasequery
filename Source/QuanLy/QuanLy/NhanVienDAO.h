#pragma once
#include <list>
#include "NhanVien.h"
using namespace std;

class CNhanVienDAO
{
public:
	CNhanVienDAO(void);
	virtual ~CNhanVienDAO(void);

	virtual size_t GetAll(list<NHANVIEN> *plstNhanVien) = 0;
	virtual bool AddNhanVien(const NHANVIEN &nhanVien, int iMaPhongBan) = 0;
	virtual bool UpdateNhanVien(const NHANVIEN &nhanVien, int iMaPhongBan) = 0;
	virtual bool DeleteNhanVien(int iMaNhanVien) = 0;
};

#pragma once
#include <list>
#include "NhanVien.h"
using namespace std;

class CPhongBanDAO
{

public:
	CPhongBanDAO(void);
	virtual size_t GetAll(list<PHONGBAN> *plstPhongBan) = 0;

	virtual ~CPhongBanDAO(void);
};

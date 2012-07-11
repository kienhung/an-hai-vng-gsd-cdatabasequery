
#define MAX_NAME 50
#define MAX_PHONE 20
#define MAX_ADDRESS 100

typedef struct	
{
	int iMaNhanVien;
	TCHAR strTenNhanVien[MAX_NAME +1];
	TCHAR cGioiTinh;
	TCHAR strSoDienThoai[MAX_PHONE +1];
	TCHAR strDiaChi[MAX_ADDRESS +1];
	TCHAR strTenPhongBan[MAX_NAME +1];
}NHANVIEN;
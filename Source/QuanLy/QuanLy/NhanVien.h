
#define MAX_NAME 50
#define MAX_PHONE 20
#define MAX_ADDRESS 100

typedef struct	
{
	int iMaNhanVien;
	char strTenNhanVien[MAX_NAME +1];
	char cGioiTinh;
	char strSoDienThoai[MAX_PHONE +1];
	char strDiaChi[MAX_ADDRESS +1];
	char strTenPhongBan[MAX_NAME +1];
}NHANVIEN;
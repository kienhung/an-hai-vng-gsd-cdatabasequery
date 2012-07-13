#include "StdAfx.h"
#include "MySQLDatabaseBuilder.h"
#include "MyException.h"

CMySQLDatabaseBuilder::CMySQLDatabaseBuilder(const char *strUser, const char *strPassword, const char *strServerAddress, const char *strDatabase, unsigned int uiPort)
{
	m_strUser = strUser;
	m_strPassword = strPassword;
	m_strServerAddress = strServerAddress;
	m_strDatabase = strDatabase;
	m_uiPort = uiPort;

	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(strUser, strPassword, strServerAddress, NULL, uiPort);
}

CMySQLDatabaseBuilder::~CMySQLDatabaseBuilder(void)
{
	if (m_pSQLDataAccessHelper  != NULL) {
		delete m_pSQLDataAccessHelper;
	}
}

void CMySQLDatabaseBuilder::Build() {


	CStringA strQuery;

	strQuery.Format("DROP DATABASE IF EXISTS %s", m_strDatabase);
	m_pSQLDataAccessHelper->ExecuteNonQuery(strQuery);

	strQuery.Format("CREATE DATABASE  IF NOT EXISTS %s  DEFAULT CHARACTER SET utf8", m_strDatabase);
	m_pSQLDataAccessHelper->ExecuteNonQuery(strQuery);

	delete m_pSQLDataAccessHelper;
	m_pSQLDataAccessHelper = new CMySQLDataAccessHelper(m_strUser, m_strPassword, m_strServerAddress, m_strDatabase, m_uiPort);

	if (NULL == m_pSQLDataAccessHelper) {
		throw new CMyException("Out Of Memory", NULL_POINTER);
	}

	strQuery = "CREATE TABLE IF NOT EXISTS `phongban` ( `MaPhong` tinyint(3) unsigned NOT NULL auto_increment, `TenPhong` varchar(100) NOT NULL,  PRIMARY KEY  (`MaPhong`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8";
	m_pSQLDataAccessHelper->ExecuteNonQuery(strQuery);
	
	strQuery = "CREATE TABLE IF NOT EXISTS `nhanvien` ( `MaNhanVien` int(10) unsigned NOT NULL auto_increment, `TenNhanVien` varchar(100) NOT NULL,  `GioiTinh` tinyint(4) NOT NULL, `DiaChi` varchar(200) NOT NULL, `SoDienThoai` varchar(40) NOT NULL, `MaPhong` tinyint(3) unsigned NOT NULL, PRIMARY KEY  (`MaNhanVien`), KEY `FK_nhanvien_phongban` (`MaPhong`), CONSTRAINT `FK_nhanvien_phongban` FOREIGN KEY (`MaPhong`) REFERENCES `phongban` (`MaPhong`) ) ENGINE=InnoDB DEFAULT CHARSET=utf8";
	m_pSQLDataAccessHelper->ExecuteNonQuery(strQuery);

	const int iLength = 78;
	char *strInserts[iLength] = {"INSERT INTO PHONGBAN(MAPHONG, TENPHONG) VALUES (1, 'Game Software Development')",
		"INSERT INTO PHONGBAN(MAPHONG, TENPHONG) VALUES (2, 'Game System Operation')",
		"INSERT INTO PHONGBAN(MAPHONG, TENPHONG) VALUES (3, 'Web Operation')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('1','Timon Fitzgerald',0,'218-1010 Porttitor Rd.','1-575-849-4461','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('2','Patrick Bradley',1,'P.O. Box 441, 5548 Eu St.','1-658-841-5879','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('3','Randall Hooper',0,'P.O. Box 329, 7792 Rhoncus. Street','1-689-460-7417','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('4','Neville Hopper',1,'6306 Fringilla Street','1-863-861-2445','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('5','Norman Fox',1,'Ap #293-2491 Ut Street','1-464-241-6768','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('6','Dean Nixon',1,'7429 Nulla. Rd.','1-732-209-5457','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('7','Owen Wolfe',0,'Ap #846-5152 Nullam Road','1-361-214-8303','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('8','Price Wright',0,'9348 Velit St.','1-724-532-4868','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('9','Hasad Glass',0,'P.O. Box 285, 9317 Pede. Rd.','1-859-287-1573','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('10','Mason Blair',0,'3711 Enim. Rd.','1-969-814-1946','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('11','Marsden Mccoy',0,'1284 Dictum Rd.','1-316-159-7558','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('12','Emerson Davis',1,'1315 Vitae, St.','1-600-170-7399','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('13','Tobias Buck',1,'P.O. Box 612, 7597 Quis Ave','1-912-825-0352','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('14','Micah Schwartz',1,'P.O. Box 873, 6466 Amet, Avenue','1-476-367-3756','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('15','Denton Leach',1,'Ap #218-3318 Nec, Street','1-165-433-7127','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('16','Todd Chapman',0,'364-7929 Praesent Road','1-283-519-9627','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('17','Kareem Sexton',1,'4654 Arcu. St.','1-907-706-9813','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('18','Hyatt Bright',0,'P.O. Box 454, 4203 Arcu Rd.','1-106-782-5228','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('19','Paul Rich',1,'P.O. Box 209, 4338 Hendrerit Rd.','1-137-478-8039','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('20','Owen Webb',1,'641-3127 Malesuada Ave','1-691-768-8130','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('21','Rogan Benson',0,'463-2711 Cursus Road','1-471-841-3886','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('22','Cade Ewing',1,'P.O. Box 235, 8438 Quam Avenue','1-258-539-0933','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('23','Lance Russo',1,'Ap #926-819 Etiam Ave','1-577-990-3103','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('24','Stewart Mcgee',0,'P.O. Box 728, 1088 Mauris St.','1-204-562-5491','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('25','Amos Meadows',1,'P.O. Box 871, 9019 Vulputate Rd.','1-282-678-4596','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('26','Andrew Stanton',1,'8300 Enim. Road','1-938-268-7862','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('27','John Conway',1,'Ap #259-3909 Phasellus Rd.','1-163-783-6190','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('28','Paul Willis',1,'P.O. Box 480, 8415 Duis St.','1-801-763-8084','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('29','Clarke Kelley',0,'9428 Turpis Street','1-898-806-8419','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('30','Leo Rose',1,'P.O. Box 410, 2733 Dignissim Avenue','1-930-363-8580','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('31','Raphael Waller',1,'371-6677 Magna Av.','1-746-214-5836','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('32','Lawrence Mccall',0,'P.O. Box 111, 7331 Ac Avenue','1-787-167-3356','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('33','Clark Hickman',1,'320-2077 Feugiat Rd.','1-158-324-8930','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('34','Beau Potter',0,'664-1740 Euismod Av.','1-818-532-5298','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('35','Bernard Walton',1,'492-487 Non, St.','1-280-187-8753','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('36','Paki Chapman',0,'8921 Ante Rd.','1-217-168-0682','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('37','Eaton Dudley',1,'P.O. Box 110, 1111 Ullamcorper Street','1-176-524-6802','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('38','Vladimir Hurley',0,'Ap #676-5406 Suspendisse Rd.','1-357-380-3936','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('39','Griffith Perez',0,'5533 Cursus St.','1-876-155-5520','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('40','Uriel Mccormick',1,'Ap #358-3465 Tellus Road','1-126-710-4916','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('41','Nolan Higgins',0,'892-127 Ridiculus Rd.','1-810-916-3590','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('42','Eagan Conner',1,'135-3402 Mi. Avenue','1-329-293-8281','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('43','Sean Winters',1,'585-3062 Vulputate, Avenue','1-953-885-9741','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('44','Rooney Hester',1,'1447 Fermentum Rd.','1-529-748-6775','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('45','Declan Stafford',1,'6160 Laoreet, Street','1-884-402-1429','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('46','Derek Black',0,'P.O. Box 984, 8904 Eget St.','1-976-598-3065','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('47','Dorian Holman',0,'P.O. Box 947, 9418 Euismod Ave','1-528-659-1004','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('48','Theodore Garrison',0,'Ap #477-1336 Parturient Av.','1-817-841-8198','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('49','Stephen Hendrix',1,'6976 Egestas St.','1-287-695-9717','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('50','Jonas Strong',1,'P.O. Box 143, 7495 Cum Rd.','1-916-825-2422','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('51','Yardley Hoover',1,'P.O. Box 347, 460 Dis St.','1-737-296-3524','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('52','Ahmed Haynes',0,'2391 Neque St.','1-445-774-1911','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('53','Henry Davis',0,'7690 Augue, St.','1-733-979-9176','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('54','Nicholas Trujillo',0,'Ap #970-9195 Auctor. Road','1-680-885-0630','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('55','Byron Reed',0,'Ap #495-7085 Neque. Ave','1-813-282-0075','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('56','Lewis Clements',0,'2757 Ante Avenue','1-146-198-8825','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('57','Norman Farley',1,'803-9483 Accumsan Rd.','1-586-192-2802','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('58','Devin Faulkner',1,'P.O. Box 766, 2343 Vulputate, Road','1-807-370-5670','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('59','Merrill Mays',1,'P.O. Box 670, 9036 Dui, Rd.','1-161-794-8888','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('60','Alec Pickett',0,'914-6296 A St.','1-166-532-7690','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('61','Richard Booker',0,'3980 A, Av.','1-671-532-2002','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('62','Wesley Stout',1,'9226 Magna Rd.','1-875-778-5885','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('63','Nero Tucker',1,'8365 Sed St.','1-398-422-3179','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('64','Mohammad Stevenson',0,'P.O. Box 295, 3488 Amet, Rd.','1-801-378-2033','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('65','Chadwick Neal',0,'P.O. Box 361, 4100 Tincidunt St.','1-203-872-3165','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('66','Alfonso Gregory',1,'P.O. Box 181, 9014 Molestie Ave','1-242-168-7698','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('67','Ezekiel Ward',0,'Ap #942-896 Orci, Ave','1-866-260-6868','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('68','Kermit Bartlett',1,'P.O. Box 736, 8404 Velit St.','1-766-695-5632','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('69','Hamish Browning',1,'923 Nullam Street','1-977-873-8119','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('70','Talon Pugh',0,'572-9776 Eu Road','1-123-487-4187','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('71','Timothy Rhodes',0,'Ap #132-4326 Natoque Rd.','1-723-900-8642','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('72','Hayes Harrell',1,'P.O. Box 565, 2384 Lorem Ave','1-430-427-2938','3')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('73','Quinlan Mccray',1,'274-3329 Magna. Rd.','1-866-110-4876','2')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('74','Aaron Wyatt',0,'8097 Rutrum Road','1-681-589-0005','1')",
		"INSERT INTO NhanVien (MaNhanVien,TenNhanVien,GioiTinh,DiaChi,SoDienThoai,MaPhong) VALUES ('75','Dane Thomas',1,'P.O. Box 120, 5398 Sem Rd.','1-683-323-2036','3')",
		};

	for (int i = 0; i < iLength; i++) {
		m_pSQLDataAccessHelper->ExecuteNonQuery(strInserts[i]);
	}

}

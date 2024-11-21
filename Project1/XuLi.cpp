#include "XuLi.h"
#include <iostream>
#include <ctime>
#include <windows.h>
void Begin(KTX& ktx) {
	ktx.KhoiTaoDsDay();
	cout << "\n\t\t\t\t\tDang vao chuong trinh . . .\n\n\t";
	for (int i = 1; i <= 100; i++) {
		cout << "|";
		Sleep(10);
	}
	system("cls");
	cout << "\n\n\n";
	cout << "\t\t==========================================================================================" << endl;
	cout << "\t\t|                                                         |                              |" << endl;
	cout << "\t\t|   ##      ##    ##########    ##########     ########   |                              |" << endl;
	cout << "\t\t|   ##      ##        ##        ##            ###   ####  |                              |" << endl;
	cout << "\t\t|   ##      ##        ##        ##                 ###    |         CHUONG TRINH         |" << endl;
	cout << "\t\t|   ##      ##        ##        ##                ###     |      QUAN LY KY TUC XA       |" << endl;
	cout << "\t\t|   ##      ##        ##        ##               ###      |             C++              |" << endl;
	cout << "\t\t|   ##      ##        ##        ##             ####   ##  |                              |" << endl;
	cout << "\t\t|   ##########        ##        ##########    ##########  |                              |" << endl;
	cout << "\t\t|                                                         |                              |" << endl;
	cout << "\t\t==========================================================================================" << endl;
	cout << endl << "\t\t";
	system("pause");
	system("cls");

	string c;
	do {
		cout << endl << endl << endl;
		cout << "\t\t\t\t===========================================================" << endl;
		cout << "\t\t\t\t[    Ban co muon nhap du lieu sinh vien tu file khong ?   ]" << endl;
		cout << "\t\t\t\t===========================================================" << endl;
		cout << "\t\t\t\t[    Co (nhan phim 'y')     |    Khong (nhan phim 'n')    ]" << endl;
		cout << "\t\t\t\t===========================================================" << endl;
		cout << "\n\t\t\t\t\t\t~> Lua chon cua ban: ";	getline(cin, c);
		if (!(c == "y" or c == "n")) cout << endl << "\t\t\t\t\t<!> Lua chon khong hop le, vui long nhap lai <!>" << endl << endl;
	} while (!(c == "y" or c == "n"));
	if (c == "y") ktx.NhapThongTinTuFile();
	XoaManHinh();
}
void menu(KTX& ktx) {
	int choice;
	do {
		cout << endl << endl;
		cout << "\t\t\t\t\t===========================================" << endl;
		cout << "\t\t\t\t\t|    Tham gia chuong trinh voi tu cach    |" << endl;
		cout << "\t\t\t\t\t| --------------------------------------- |" << endl;
		cout << "\t\t\t\t\t|   1. Sinh vien                          |" << endl;
		cout << "\t\t\t\t\t|   2. Ban quan ly                        |" << endl;
		cout << "\t\t\t\t\t|   0. Thoat chuong trinh                 |" << endl;
		cout << "\t\t\t\t\t===========================================" << endl;
		cout << "\n\t\t\t\t\t~> Lua chon cua ban(0,1,2): "; cin >> choice; cin.ignore();
		switch (choice) {
		case 0:
			cout << "\t\t\t\t\t<> Thoat chuong trinh <>" << endl;
			break;
		case 1:
			XoaManHinh();
			SVChoice(ktx);
			break;
		case 2:
			XoaManHinh();
			menuBQL(ktx);
			break;
		default:
			cout << "\t\t\t\t\t\t<!> Lua chon khong hop le <!>" << endl;
		}
	} while (choice != 0);
}
void menuBQL(KTX& ktx) {
	int choice;
	do {
		cout << endl << endl;
		cout << "\t\t\t\t\tO ------ Chon doi tuong thuc hien ------ O" << endl;
		cout << "\t\t\t\t\t| 1. Sinh vien                           |" << endl;
		cout << "\t\t\t\t\t| 2. Day / Phong                         |" << endl;
		cout << "\t\t\t\t\t| 0. Quay lai                            |" << endl;
		cout << "\t\t\t\t\tO ---------------------------------------O" << endl;
		cout << "\n\t\t\t\t\t~> Nhap lua chon: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 0:
			XoaManHinh();
			break;
		case 1:
			XoaManHinh();
			menuSV(ktx);
			break;
		case 2:
			XoaManHinh();
			menuDayPhong(ktx);
			break;
		default:
			cout << endl << "\t\t\t\t\t<!> Lua chon khong hop le <!>" << endl << endl;
		}
	} while (choice != 0);
}
void SVChoice(KTX& ktx) {
	int choice;
	do {
		cout << endl << endl;
		cout << "\t\t\t\t\tO ------ QUAN LY SINH VIEN ------ O" << endl;
		cout << "\t\t\t\t\t| 1. Dang ky Ki tuc xa            |" << endl;
		cout << "\t\t\t\t\t| 2. Xem danh sach sinh vien      |" << endl;
		cout << "\t\t\t\t\t| 3. Thanh toan tien dien         |" << endl;
		cout << "\t\t\t\t\t| 0. Quay lai                     |" << endl;
		cout << "\t\t\t\t\tO --------------------------------O" << endl;
		cout << "\n\t\t\t\t\t~> Nhap lua chon: ";
		cin >> choice; cin.ignore();

		switch (choice) {
		case 0: XoaManHinh(); break;
		case 1:
			cout << "\n\t\t\t\t\t1. Dang ky Ki tuc xa " << endl<<endl;
			ktx.DangKySV();
			cout << endl<<"\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		case 2:
			cout << "\n\t\t\t\t\t2. Xem danh sach sinh vien " << endl << endl;
			ktx.XemDanhSachSV2();
			cout << endl;
			system("pause");
			XoaManHinh();
			break;
		case 3:
			cout << "\n\t\t\t\t\t3. Thanh toan tien dien  " << endl << endl;
			ktx.ThanhToanTienDien();
			cout << endl<<"\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		default:
			cout << endl << "\t\t\t\t\t<!> Lua chon khong hop le <!>" << endl << endl;
		}
	} while (choice != 0);
}

void menuSV(KTX& ktx) {
	int choice;
	do {
		cout << endl << endl;
		cout << "\t\t\t\t\tO --------- QUAN LI SINH VIEN --------- O" << endl;
		cout << "\t\t\t\t\t| 1. Them sinh vien                     |" << endl;
		cout << "\t\t\t\t\t| 2. Xuat danh sach sinh vien           |" << endl;
		cout << "\t\t\t\t\t| 3. Tra cuu sinh vien                  |" << endl;
		cout << "\t\t\t\t\t| 4. Xoa sinh vien                      |" << endl;
		cout << "\t\t\t\t\t| 5. Duyet sinh vien                    |" << endl;
		cout << "\t\t\t\t\t| 6. Luu danh sach sinh vien vao file   |" << endl;
		cout << "\t\t\t\t\t| 0. Quay lai                           |" << endl;
		cout << "\t\t\t\t\tO --------------------------------------O" << endl;
		cout << "\n\t\t\t\t\t~> Nhap lua chon: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 0:
			XoaManHinh();
			break;
		case 1:
			cout << "\n\t\t\t\t\t1. Them sinh vien " << endl << endl;
			cout << endl << "\t\t\t\t\t> Bat dau nhap sinh vien ben duoi <" << endl;
			ktx.NhapSinhVien();
			cout << endl<<"\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		case 2:
			XoaManHinh();
			menuSV2(ktx);
			break;
		case 3:
			XoaManHinh();
			menuSV3(ktx);
			break;
		case 4:
		{
			cout << "\n\t\t\t\t\t 4. Xoa sinh vien " << endl << endl;
			string hoTen, mssv, tenPhong, tenDay;
			cout << "\t\t\t\t\t> Nhap thong tin sinh vien can xoa <" << endl;
			do {
				cout << "\t\t\t\t\tNhap Ho Ten: "; getline(cin, hoTen);
				if (!(CoDauCach(hoTen))) cout << "\t\t\t\t\t<!> Ho ten da nhap khong hop le <!>" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
			} while (!(CoDauCach(hoTen)));
			do {
				cout << "\t\t\t\t\tNhap MSSV: "; getline(cin, mssv);
				if (CoDauCach(mssv) or mssv.size() != 10) cout << "\t\t\t\t\t<!> MSSV da nhap khong hop le <!>" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
			} while (CoDauCach(mssv) or mssv.size() != 10);
			do {
				cout << "\t\t\t\t\tNhap ten day: "; getline(cin, tenDay);
				if (CoDauCach(tenDay) or ktx.TenDayInt(tenDay) < 0 or ktx.TenPhongInt(tenPhong) > 4) cout << "\t\t\t\t\t<!> Ten day da nhap khong hop le <!>" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
			} while (CoDauCach(tenDay) or ktx.TenDayInt(tenDay) < 0 or ktx.TenPhongInt(tenDay) > 4);
			do {
				cout << "\t\t\t\t\tNhap ten phong: "; getline(cin, tenPhong);
				if (CoDauCach(tenPhong) or ktx.TenPhongInt(tenPhong) < 0 or ktx.TenPhongInt(tenPhong) > 4) cout << "\t\t\t\t\t<!> Ten phong da nhap khong hop le <!>" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
			} while (CoDauCach(tenPhong) or ktx.TenPhongInt(tenPhong) < 0 or ktx.TenPhongInt(tenPhong) > 4);
			ktx.XoaSinhVien(hoTen, mssv, tenDay, tenPhong);
			cout << endl<< "\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		}
		case 5:
			cout << "\n\t\t\t\t\t5. Duyet sinh vien " << endl << endl;
			ktx.DuyetSV();
			cout << endl<<"\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		case 6:
			cout << "\n\t\t\t\t\t6. Luu danh sach sinh vien vao file " << endl << endl;
			ktx.LuuDanhSachSV();
			cout << endl << "\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		default:
			cout << endl << "\t\t\t\t<!> Lua chon khong hop le <!>" << endl << endl;
		}
	} while (choice != 0);
}
void menuSV2(KTX& ktx) {
	int choice;
	do {
		cout << endl << endl;
		cout << "\t\t\t\t\tO ----------- Xuat sinh vien ----------- O" << endl;
		cout << "\t\t\t\t\t| 1. Xuat sinh vien theo bang chu cai    |" << endl;
		cout << "\t\t\t\t\t| 2. Xuat sinh vien theo day phong       |" << endl;
		cout << "\t\t\t\t\t| 3. Xuat sinh vien mac dinh             |" << endl;
		cout << "\t\t\t\t\t| 0. Quay lai                            |" << endl;
		cout << "\t\t\t\t\tO ---------------------------------------O" << endl;
		cout << "\n\t\t\t\t\t~> Nhap lua chon: ";
		cin >> choice; cin.ignore();

		switch (choice) {
		case 0: XoaManHinh(); break;
		case 1:
			cout << "\n\t\t\t\t\t1. Xuat sinh vien theo bang chu cai " << endl << endl;
			ktx.XuatDsSinhVienTheoBangChuCai();
			cout << endl;
			system("pause");
			XoaManHinh();
			break;
		case 2:
			cout << "\n\t\t\t\t\t2. Xuat sinh vien theo day phong " << endl << endl;
			ktx.XuatDsSinhVienTheoDayPhong();
			cout << endl;
			system("pause");
			XoaManHinh();
			break;
		case 3:
			cout << "\n\t\t\t\t\t3. Xuat sinh vien mac dinh " << endl << endl;
			ktx.XuatDsSinhVien();
			cout << endl;
			system("pause");
			XoaManHinh();
			break;
		default:
			cout << endl << "\t\t\t\t\t<!> Lua chon khong hop le <!>" << endl << endl;
		}
	} while (choice != 0);
}

void menuSV3(KTX& ktx) {
	int choice;
	do {
		cout << "\n\n\t\t\t\t\tO -------- TRA CUU SINH VIEN -------- O" << endl;
		cout << "\t\t\t\t\t| 1. Tra cuu sinh vien theo ten       |" << endl;
		cout << "\t\t\t\t\t| 2. Tra cuu sinh vien theo MSSV      |" << endl;
		cout << "\t\t\t\t\t| 0. Quay lai                         |" << endl;
		cout << "\t\t\t\t\tO ------------------------------------O" << endl;
		cout << "\n\t\t\t\t\t~> Nhap lua chon: ";
		cin >> choice; cin.ignore();

		switch (choice) {
		case 0: XoaManHinh(); break;
		case 1:
		{
			cout << "\n\t\t\t\t\t1. Tra cuu sinh vien theo ten " << endl << endl;
			string ten;
			do {
				cout << "\n\t\t\t\t\t->Nhap ten sinh vien can tra cuu: ";
				getline(cin, ten);
				if (CoDauCach(ten))
					cout << "\t\t\t\t\tTen khong duoc chua khoang cach!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
			} while (CoDauCach(ten));
			ktx.TimSinhVienTheoTen(ten);
			cout << endl<< "\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		}
		case 2:
		{
			cout << "\n\t\t\t\t\t2. Tra cuu sinh vien theo MSSV " << endl << endl;
			string mssv;
			do {
				cout << "\n\t\t\t\t\t->Nhap MSSV can tra cuu: ";
				getline(cin, mssv);
				if (mssv.size() != 10 or CoDauCach(mssv)) cout << "\t\t\t\t\tMSSV vua nhap khong hop le!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
			} while (mssv.size() != 10 or CoDauCach(mssv));
			ktx.TimSinhVienTheoMSSV(mssv);
			cout << endl<< "\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		}
		default:
			cout << endl << "\t\t\t\t<!> Lua chon khong hop le <!>" << endl << endl;
		}
	} while (choice != 0);
}
void menuDayPhong(KTX& ktx) {
	int choice;
	do {
		cout << endl << endl;
		cout << "\t\t\t\t\tO ----- BANG CHUC NANG DAY/PHONG ----- O" << endl;
		cout << "\t\t\t\t\t| 1. Hien thong tin day                |" << endl;
		cout << "\t\t\t\t\t| 2. Hien danh sach phong con trong    |" << endl;
		cout << "\t\t\t\t\t| 3. Xem thong tin phong               |" << endl;
		cout << "\t\t\t\t\t| 4. Nhap so dien                      |" << endl;
		cout << "\t\t\t\t\t| 5. Xem trang thai dong tien dien     |" << endl;
		cout << "\t\t\t\t\t| 0. Quay lai                          |" << endl;
		cout << "\t\t\t\t\tO -------------------------------------O" << endl;
		cout << "\n\t\t\t\t\t~> Nhap lua chon: ";
		cin >> choice; cin.ignore();

		switch (choice) {
		case 0:
			XoaManHinh();
			break;
		case 1:
			cout << "\n\t\t\t\t\t1. Hien thong tin day " << endl << endl;
			ktx.HienThiThongTinDay();
			cout << endl<<"\t\t";
			system("pause");
			XoaManHinh();
			break;
		case 2:
			cout << "\n\t\t\t\t\t2. Hien danh sach phong con trong " << endl << endl;
			ktx.HienPhongTrong();
			cout << endl << "\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		case 3:
			cout << "\n\t\t\t\t\t3. Xem thong tin phong " << endl << endl;
			ktx.XemThongTinCacPhong();
			cout << endl << "\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		case 4:
			XoaManHinh();
			menuDayPhong4(ktx);
			break;
		case 5:
			cout << "\n\t\t\t\t\t5. Xem trang thai dong tien dien " << endl << endl;
			ktx.XemTinhTrangDongTienDien();
			cout << endl << "\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			break;
		default:
			cout << endl << "\t\t\t\t\t<!> Lua chon khong hop le <!>" << endl << endl;
		}
	} while (choice != 0);
}
void menuDayPhong4(KTX& ktx) {
	int choice;
	do {
		cout << endl << endl;
		cout << "\t\t\t\t\tO ---------- NHAP SO DIEN ---------- O" << endl;
		cout << "\t\t\t\t\t| 1. Nhap thu cong                   |" << endl;
		cout << "\t\t\t\t\t| 2. Nhap tu file du lieu            |" << endl;
		cout << "\t\t\t\t\t| 0. Quay lai                        |" << endl;
		cout << "\t\t\t\t\tO -----------------------------------O" << endl;
		cout << "\n\t\t\t\t\t~> Nhap lua chon: ";
		cin >> choice; cin.ignore();
		switch (choice) {
		case 0:
			XoaManHinh();
			break;
		case 1:
			cout << "\n\t\t\t\t\t1. Nhap thu cong " << endl << endl;
			ktx.NhapSoDien();
			cout << endl << "\t\t\t\t\t";
			system("pause");
			XoaManHinh();
			choice = 0;
			break;
		case 2:
			cout << "\n\t\t\t\t\t2. Nhap tu file du lieu  " << endl << endl;
			ktx.NhapSoDienFile();
			cout << endl << "\t\t\t\t\t";
			system("pause");
			XoaManHinh();

			choice = 0;
			break;
		default:
			cout << endl << "\t\t\t\t<!> Lua chon khong hop le <!>" << endl << endl;
		}
	} while (choice != 0);
}
void XoaManHinh() { system("cls"); }

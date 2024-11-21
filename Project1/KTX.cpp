#include "KTX.h"
int KTX::getSoLuongDay() { return SoLuongDay; }
void KTX::setSoLuongDay(int soLuongDay) {
	SoLuongDay = soLuongDay;
}
void KTX::KhoiTaoDsDay() {
	SoLuongDay = 4;
	DsDay.resize(SoLuongDay);
	for (int i = 0; i < SoLuongDay; i++) {
		DsDay[i].KhoiTaoDay(i);
	}
}
void KTX::ThemSinhVien(SinhVien sv, int thuTuDay, int thuTuPhong) {
	DsDay[thuTuDay].NhapSinhVien(sv, thuTuPhong);
}

void KTX::NhapThongTinTuFile() {
	ifstream file("DanhSachSinhVien.txt");
	if (!file.is_open()) {
		cout << "Loi: Khong the mo file de doc!" << endl;
	}
	// Đọc 3 byte đầu tiên để kiểm tra BOM
	char bom[3] = { 0 };
	file.read(bom, 3);
	// Kiểm tra nếu file có BOM (UTF-8 BOM: EF BB BF)
	if (bom[0] != '\xEF' || bom[1] != '\xBB' || bom[2] != '\xBF') {
		// Không phải BOM, quay lại từ đầu
		file.seekg(0);
	}
	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string hoTen, mssv, diaChi, lop, khoa, gioiTinh, sdt;
		int ngay, thang, nam;
		int thuTuDay, thuTuPhong;

		getline(ss, hoTen, ',');
		getline(ss, mssv, ',');
		getline(ss, diaChi, ',');
		getline(ss, lop, ',');
		getline(ss, khoa, ',');
		getline(ss, gioiTinh, ',');
		getline(ss, sdt, ',');
		ss >> ngay; ss.ignore();
		ss >> thang; ss.ignore();
		ss >> nam; ss.ignore();
		ss >> thuTuDay; ss.ignore();
		ss >> thuTuPhong;

		Date ngaySinh(ngay, thang, nam);
		SinhVien sv(hoTen, mssv, diaChi, lop, khoa, gioiTinh, sdt, ngaySinh);

		ThemSinhVien(sv, thuTuDay, thuTuPhong);
	}
	cout << "Da Nhap";
	file.close();
}

void KTX::NhapSinhVien() {
	SinhVien sv;
	cout << "\t\t\t\t\t<Luu y: Viet hoa chu cai dau>" << endl << endl;
	sv.Nhap();
	if (!(KiemTraMSSV(sv.getMSSV()))) {
		cout << "\t\t\t\t\tMSSV da nhap khong hop le hoac da trung!";
		return;
	}
	if (!(sv.KiemTraKhoa())) {
		return;
	}
	int dem = 0;
	cout << "\t\t\t\t\tDanh sach phong con trong:" << endl;
	XuatDsPhongTrong(sv.getGioiTinh(), dem);
	if (dem == 0) {
		cout << endl << "\t\t\t\t\tKhong the them sinh vien vao KTX!" << endl;
		return;
	}

	string thuTuDayStr, thuTuPhongStr;
	int thuTuPhong, thuTuDay;
	do {
		cout << "\n\t\t\t\t\tNhap ten day: ";
		cin >> thuTuDayStr; cin.ignore();
		cout << "\t\t\t\t\tNhap ten phong: ";
		cin >> thuTuPhongStr; cin.ignore();
		thuTuDay = TenDayInt(thuTuDayStr);
		thuTuPhong = TenPhongInt(thuTuPhongStr);
		if ((thuTuDay < 0 or thuTuDay>3) and (thuTuPhong < 0 or thuTuPhong>3)) cout << "\t\t\t\t\tDay va phong da nhap khong hop le!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
	} while (((thuTuDay < 0 or thuTuDay>3) and (thuTuPhong < 0 or thuTuPhong>3)));

	if (KiemTraPhongTrong(thuTuDay, thuTuPhong, sv.getGioiTinh())) {
		ThemSinhVien(sv, thuTuDay, thuTuPhong);
		cout << "\t\t\t\t\tDa them sinh vien" << endl;
	}
	else {
		cout << "\t\t\t\t\tPhong da day hoac thong tin nhap vao khong hop le!" << endl << endl;
	}

}

void KTX::XuatDsSinhVien() {
	// Xuất tiêu đề bảng
	cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
	cout <<"|"<< setw(7) << "Day |" << setw(9) << "Phong |" << setw(22) << "Ho ten |" << setw(15) << "MSSV |" << setw(13) << "Lop |" << setw(9) << "Khoa |" << setw(17) << "Dia Chi |" << setw(10) << "GTinh |" << setw(15) << "SDT |" << setw(16) << "Ngay sinh |\n";
	cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		for (int j = 0; j < danhSachPhong.size(); j++) {
			vector<SinhVien> danhSachSV = danhSachPhong[j].getDsSV();
			for (int k = 0; k < danhSachSV.size(); k++) {
				cout <<"|"<< setw(5) << DsDay[i].getTenDay() << " |" << setw(7) << danhSachPhong[j].getTenPhong() << " |";
				danhSachSV[k].XuatBang();
			}
			cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
		}
	}
}
void KTX::XuatDsSinhVienTheoBangChuCai() {
	cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "|" << setw(7) << "Day |" << setw(9) << "Phong |" << setw(22) << "Ho ten |" << setw(15) << "MSSV |" << setw(13) << "Lop |" << setw(9) << "Khoa |" << setw(17) << "Dia Chi |" << setw(10) << "GTinh |" << setw(15) << "SDT |" << setw(16) << "Ngay sinh |\n";
	cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
	string ten;
	for (char c = 'A'; c <= 'Z'; c++) {
		for (int i = 0; i < DsDay.size(); i++) {
			vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
			for (int j = 0; j < danhSachPhong.size(); j++) {
				vector<SinhVien> danhSachSV = danhSachPhong[j].getDsSV();
				for (int k = 0; k < danhSachSV.size(); k++) {
					ten = danhSachSV[k].getTen();
					if (ten[0] == c) {
						cout << "|" << setw(5) << DsDay[i].getTenDay() << " |" << setw(7) << danhSachPhong[j].getTenPhong() << " |";
						danhSachSV[k].XuatBang();
					}
				}
			}
		}
	}
	cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
}
void KTX::XuatDsSinhVienTheoDayPhong() {
	string tenDay, tenPhong;
	do {
		cout << "\t\t\t\t\t~> Nhap ten day: ";
		getline(cin, tenDay);
		if (tenDay != "D1" and tenDay != "D2" and tenDay != "N1" and tenDay != "N2") {
			cout << "\t\t\t\t\tTen day da nhap khong dung!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl;
			cout << "\t\t\t\t\t[D1, D2, N1, N2]" << endl;
		}
	} while (tenDay != "D1" and tenDay != "D2" and tenDay != "N1" and tenDay != "N2");

	do {
		cout << "\t\t\t\t\t~> Nhap ten phong: ";
		getline(cin, tenPhong);
		if (tenPhong != "P01" and tenPhong != "P02" and tenPhong != "P03" and tenPhong != "P04") {
			cout << "\t\t\t\t\tTen phong da nhap khong dung!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl;
			cout << "\t\t\t\t\t[P01, P02, P03, P04]" << endl;
		}
	} while (tenPhong != "P01" and tenPhong != "P02" and tenPhong != "P03" and tenPhong != "P04");

	for (int i = 0; i < DsDay.size(); i++) {
		if (DsDay[i].getTenDay() == tenDay) {
			vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
			for (int j = 0; j < danhSachPhong.size(); j++) {
				if (danhSachPhong[j].getTenPhong() == tenPhong) {
					cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
					cout << "|" << setw(7) << "Day |" << setw(9) << "Phong |" << setw(22) << "Ho ten |" << setw(15) << "MSSV |" << setw(13) << "Lop |" << setw(9) << "Khoa |" << setw(17) << "Dia Chi |" << setw(10) << "GTinh |" << setw(15) << "SDT |" << setw(16) << "Ngay sinh |\n";
					cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";

					vector<SinhVien> danhSachSV = danhSachPhong[j].getDsSV();
					for (int k = 0; k < danhSachSV.size(); k++) {
						cout << "|" << setw(5) << DsDay[i].getTenDay() << " |" << setw(7) << danhSachPhong[j].getTenPhong() << " |";
						danhSachSV[k].XuatBang();
					}
				}
			}
			cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
			return;
		}
	}
}
void KTX::XemDanhSachSV2() {
	cout << "\t\t----------------------------------------------------------------------------------------\n";
	cout << "\t\t|"<<setw(7) << "Day |" << setw(10) << "Phong |" << setw(25) << "Ho ten |" << setw(20) << "MSSV |" << setw(15) << "Lop |" << setw(10) << "Khoa |" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------\n";
	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		for (int j = 0; j < danhSachPhong.size(); j++) {
			vector<SinhVien> danhSachSV = danhSachPhong[j].getDsSV();
			for (int k = 0; k < danhSachSV.size(); k++) {
				cout << "\t\t|"<<setw(5) << DsDay[i].getTenDay() << " |" << setw(8) << danhSachPhong[j].getTenPhong() << " |";
				danhSachSV[k].XuatDonGian();
			}
		}
		cout << "\t\t----------------------------------------------------------------------------------------\n";
	}

}
void KTX::XuatDsPhongTrong(string gioiTinh, int& dem) {
	for (int i = 0; i < DsDay.size(); i++) {
		for (int j = 0; j < DsDay[i].getSoLuongPhong(); j++) {
			if (KiemTraPhongTrong(i, j, gioiTinh)) {
				if (dem == 0) cout << "\t\t\t\t\t";
				cout << "|"; DsDay[i].XuatTenPhong(i, j); cout << "|   ";
				dem++;
			}
		}
	}
	if (dem == 0) cout << "\t\t\t\t\tKTX khong con phong trong";
}

void KTX::LuuDanhSachSV() {
	ofstream XoaFile("DanhSachSinhVien.txt", ostream::out | ostream::trunc);
	XoaFile.close();

	ofstream file("DanhSachSinhVien.txt", ios::app);
	if (!file.is_open()) {
		cout << "\t\t\t\t\tKhong the mo file DanhSachSinhVien.txt"<<endl;
	}
	else {
		for (int i = 0; i < DsDay.size(); i++) {
			vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
			for (int j = 0; j < danhSachPhong.size(); j++) {
				vector<SinhVien> danhSachSV = danhSachPhong[j].getDsSV();
				for (int k = 0; k < danhSachSV.size(); k++) {
					file << danhSachSV[k].getHoTen() << ",";
					file << danhSachSV[k].getMSSV() << ",";
					file << danhSachSV[k].getDiaChi() << ",";
					file << danhSachSV[k].getLop() << ",";
					file << danhSachSV[k].getKhoa() << ",";
					file << danhSachSV[k].getGioiTinh() << ",";
					file << danhSachSV[k].getSDT() << ",";
					file << danhSachSV[k].getNgaySinh().getNgay() << "/";
					file << danhSachSV[k].getNgaySinh().getThang() << "/";
					file << danhSachSV[k].getNgaySinh().getNam() << ",";
					file << DsDay[i].getThuTuDay() << ",";
					file << danhSachPhong[j].getThuTuPhong() << endl;
				}
			}
		}
		file.close();
		cout << "\t\t\t\t\tDa luu danh sach sinh vien vao file" << endl;
	}
}

bool KTX::KiemTraMSSV(string mssv) {
	bool kt = true;
	for (int i = 0; i < DsDay.size(); i++) {
		kt = DsDay[i].KiemTraMSSV(mssv);
		if (kt == false) return kt;
	}
	return kt;
}
bool KTX::KiemTraPhongTrong(int thuTuDay, int thuTuPhong, string gioiTinh) {
	return DsDay[thuTuDay].KiemTraPhongTrong(thuTuDay, thuTuPhong, gioiTinh);
}

int KTX::TenDayInt(string tenDay) {

	if (tenDay == "D1") return 0;
	else if (tenDay == "D2") return 1;
	else if (tenDay == "N1") return 2;
	else  return 3;
}
int KTX::TenPhongInt(string tenPhong) {
	if (tenPhong == "P01") return 0;
	else if (tenPhong == "P02") return 1;
	else if (tenPhong == "P03") return 2;
	else return 3;
}
string KTX::ThuTuDayStr(int thuTuDay) {
	if (thuTuDay == 0) return "D1";
	else if (thuTuDay == 1) return "D2";
	else if (thuTuDay == 2) return "N1";
	else  return "N2";
}
string KTX::ThuTuPhongStr(int thuTuPhong) {
	if (thuTuPhong == 0) return "P01";
	else if (thuTuPhong == 1) return "P02";
	else if (thuTuPhong == 2) return "P03";
	else  return "P04";
}

void KTX::TimSinhVienTheoTen(string ten) {
	bool found = false;
	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		for (int j = 0; j < danhSachPhong.size(); j++) {
			vector<SinhVien> danhSachSV = danhSachPhong[j].getDsSV();
			for (int k = 0; k < danhSachSV.size(); k++) {
				if (danhSachSV[k].getTen() == ten) {
					if (found == false) {
						cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
						cout << "|" << setw(7) << "Day |" << setw(9) << "Phong |" << setw(22) << "Ho ten |" << setw(15) << "MSSV |" << setw(13) << "Lop |" << setw(9) << "Khoa |" << setw(17) << "Dia Chi |" << setw(10) << "GTinh |" << setw(15) << "SDT |" << setw(16) << "Ngay sinh |\n";
						cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
					}
					cout <<"|"<< setw(5) << DsDay[i].getTenDay() << " |" << setw(7) << danhSachPhong[j].getTenPhong() << " |";
					danhSachSV[k].XuatBang();
					found = true;
				}
			}
		}
	}
	if (found) cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
	else cout << "\t\t\t\t\tKhong tim thay sinh vien" << endl;
}
void KTX::TimSinhVienTheoMSSV(string mssv) {
	bool found = false;
	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		for (int j = 0; j < danhSachPhong.size(); j++) {
			vector<SinhVien> danhSachSV = danhSachPhong[j].getDsSV();
			for (int k = 0; k < danhSachSV.size(); k++) {
				if (danhSachSV[k].getMSSV() == mssv) {
					if (found == false) {
						cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
						cout << "|" << setw(7) << "Day |" << setw(9) << "Phong |" << setw(22) << "Ho ten |" << setw(15) << "MSSV |" << setw(13) << "Lop |" << setw(9) << "Khoa |" << setw(17) << "Dia Chi |" << setw(10) << "GTinh |" << setw(15) << "SDT |" << setw(16) << "Ngay sinh |\n";
						cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
					}
					cout <<"|"<< setw(5) << DsDay[i].getTenDay() << " |" << setw(7) << danhSachPhong[j].getTenPhong() << " |";
					danhSachSV[k].XuatBang();
					found = true;
				}
			}
		}
	}
	if (found) cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
	else cout << "\t\t\t\t\tKhong tim thay sinh vien" << endl;
}
void KTX::XoaSinhVien(string hoTen, string mssv, string tenDay, string tenPhong) {
	bool kt = false;
	for (int i = 0; i < DsDay.size(); i++) {
		if (DsDay[i].getTenDay() == tenDay) {
			vector<Phong>* danhSachPhongPtr = DsDay[i].getDsPhongPtr();
			for (int j = 0; j < danhSachPhongPtr->size(); j++) {
				if (danhSachPhongPtr->at(j).getTenPhong() == tenPhong) {
					vector<SinhVien>* danhSachSVPtr = danhSachPhongPtr->at(j).getDsSVPtr();
					for (int k = 0; k < danhSachSVPtr->size(); k++) {
						if (danhSachSVPtr->at(k).getHoTen() == hoTen and danhSachSVPtr->at(k).getMSSV() == mssv) {
							danhSachSVPtr->erase(danhSachSVPtr->begin() + k);
							kt = true;
							danhSachPhongPtr->at(j).setSoNguoiHienTai(danhSachPhongPtr->at(j).getSoNguoiHienTai() - 1);
						}
					}
				}
			}
		}
	}
	if (!kt) cout << "\t\t\t\t\tKhong tim thay sinh vien!" << endl << endl;
	else cout << "\t\t\t\t\tXoa sinh vien thanh cong!" << endl << endl;
}
void KTX::HienThiThongTinDay() {
	cout<<"\t\t";
	for (int i = 0; i < DsDay.size(); i++) {
		cout << "----------------------\t";
	}
	cout << endl<<"\t\t";
	for (int i = 0; i < DsDay.size(); i++) {
		cout << "|       Day " << DsDay[i].getTenDay() << "       |\t";
	}
	cout << endl << "\t\t";
	for (int i = 0; i < DsDay.size(); i++) {
		//		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		cout << "| So luong phong: " << DsDay[i].getSoLuongPhong() << "  |\t";
	}
	cout << endl << "\t\t";
	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		cout << "|    Loai day: " << setw(3) << DsDay[i].getLoaiDay() << "   |\t";
	}
	cout << endl << "\t\t";
	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		int dem = 0;
		for (int i = 0; i < danhSachPhong.size(); i++) {
			if (danhSachPhong[i].KiemTraPhongTrong()) dem++;
		}
		cout << "| TTrang: ";
		if (dem != 0) cout << "Con phong  |\t";
		else cout << "Het phong  |\t";
	}
	cout << endl << "\t\t";

	for (int i = 0; i < DsDay.size(); i++) {
		cout << "----------------------\t";
	}
}
void KTX::HienPhongTrong() {
	bool kt = false, ktDay = false, ktPhong = false;
	for (int i = 0; i < DsDay.size(); i++) {
		ktDay = false;
		vector<Phong> danhSachPhong = DsDay[i].getDsPhong();
		ktPhong = false;
		for (int j = 0; j < danhSachPhong.size(); j++) {
			if (danhSachPhong[j].KiemTraPhongTrong()) {
				if (kt == false) cout << "\n\t\t\t\t\t--- Danh sach cac phong con trong ---" << endl;
				if (ktDay == false) cout << endl <<"\t\t\t\t\t"<< DsDay[i].getTenDay() << ": ";
				cout << danhSachPhong[j].getTenPhong() << "  ";
				kt = ktDay = true;
			}
		}
	}
	if (!kt) cout << "\t\t\t\t\tKhong con phong trong" << endl << endl;
	else cout << endl << endl;
}
void KTX::XemThongTinCacPhong() {
	cout << "\t\t\t------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t|"<<setw(5) << "Day |" << setw(7) << "Ten |" << setw(12) << "So nguoi |" << setw(14) << "So dien cu |" << setw(14) << "So dien moi |" << setw(12) << "Tien dien |" << setw(10) << " Trang thai |" << endl;
	cout << "\t\t\t------------------------------------------------------------------------------" << endl;
	for (int j = 0; j < DsDay.size(); j++) {
		vector<Phong> danhSachPhong = DsDay[j].getDsPhong();

		for (int i = 0; i < danhSachPhong.size(); i++) {
			cout <<"\t\t\t|"<< setw(3) << DsDay[j].getTenDay() << " |" << setw(5) << danhSachPhong[i].getTenPhong() << " |" << setw(8) << danhSachPhong[i].getSoNguoiHienTai() << "/" << danhSachPhong[i].getSoNguoiToiDa() << " |" << setw(12) << danhSachPhong[i].getSoDienCu() << " |" << setw(12) << danhSachPhong[i].getSoDienMoi() << " |" << setw(10) << danhSachPhong[i].getTienDien() << " |";
			if (danhSachPhong[i].getTrangThai() == 0) cout << setw(13) << "Chua dong |" << endl;
			else cout << setw(13) << "Da dong |" << endl;
		}
		cout << "\t\t\t------------------------------------------------------------------------------" << endl;
	}
}
void KTX::NhapSoDien() {
	float soDien;
	cout << "\n\t\t\t\t\t--- Nhap so dien ---" << endl;
	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong>* danhSachPhongPtr = DsDay[i].getDsPhongPtr();
		for (int j = 0; j < danhSachPhongPtr->size(); j++) {
			cout << endl << "\t\t\t\t"<<DsDay[i].getTenDay() << "-" << danhSachPhongPtr->at(j).getTenPhong();
			cout << "\tSo dien cu: " << danhSachPhongPtr->at(j).getSoDienCu() << "\tSo dien moi: "<<danhSachPhongPtr->at(j).getSoDienMoi()<<"\tTrang Thai:";
			if (danhSachPhongPtr->at(j).getTrangThai() == true) cout << "Da dong" << endl;
			else cout << "Chua dong" << endl;
			if (danhSachPhongPtr->at(j).getTrangThai() == true) danhSachPhongPtr->at(j).setSoDienCu(danhSachPhongPtr->at(j).getSoDienMoi());
			do {
				cout << "\t\t\t\t\t->Nhap so dien thang nay: ";
				cin >> soDien; cin.ignore();
				if (soDien < danhSachPhongPtr->at(j).getSoDienMoi()) cout << "\t\t\t\t\tSo dien da nhap khong duoc nho hon so dien thang truoc!" << "Vui long nhap lai!" << endl << endl;
			} while (soDien < danhSachPhongPtr->at(j).getSoDienMoi());

			danhSachPhongPtr->at(j).setSoDienMoi(soDien);
			danhSachPhongPtr->at(j).setTrangThai(false);
			danhSachPhongPtr->at(j).TinhTienDien();
		}
	}
}

void KTX::NhapSoDienFile() {
	ifstream file("SoDien.txt");
	float soDien;
	if (!file.is_open()) {
		cout << "\t\t\t\t\tKhong the mo file SoDien.txt";
		return;
	}
	for (int i = 0; i < DsDay.size(); i++) {
		vector<Phong>* danhSachPhongPtr = DsDay[i].getDsPhongPtr();
		for (int j = 0; j < danhSachPhongPtr->size(); j++) {
			danhSachPhongPtr->at(j).setSoDienCu(danhSachPhongPtr->at(j).getSoDienMoi());
			file >> soDien;
			danhSachPhongPtr->at(j).setSoDienMoi(soDien);
			danhSachPhongPtr->at(j).setTrangThai(false);
			danhSachPhongPtr->at(j).TinhTienDien();
		}
	}
	cout << "\t\t\t\t\tDa nhap so dien tu file thanh cong!" << endl;
	file.close();
}
void KTX::XemTinhTrangDongTienDien() {
	bool kt = false;
	for (int i = 0; i < DsDay.size(); i++) {
		vector <Phong> danhSachPhong = DsDay[i].getDsPhong();
		for (int j = 0; j < danhSachPhong.size(); j++) {
			if (danhSachPhong[j].getTrangThai() == false) {
				if (kt == false) {
					cout << "\t\t\t------------------------------------------------------------------------------" << endl;
					cout << "\t\t\t|"<<setw(5) << "Day |" << setw(7) << "Ten |" << setw(12) << "So nguoi |" << setw(14) << "So dien cu |" << setw(14) << "So dien moi |" << setw(12) << "Tien dien |" << setw(10) << " Trang thai |" << endl;
					cout << "\t\t\t------------------------------------------------------------------------------" << endl;
				}
				cout << "\t\t\t|" <<setw(3) << DsDay[i].getTenDay() << " |" << setw(5) << danhSachPhong[j].getTenPhong() << " |" << setw(8) << danhSachPhong[j].getSoNguoiHienTai() << "/" << danhSachPhong[j].getSoNguoiToiDa() << " |" << setw(12) << danhSachPhong[j].getSoDienCu() << " |" << setw(12) << danhSachPhong[j].getSoDienMoi() << " |" << setw(10) << danhSachPhong[j].getTienDien() << " |";
				if (danhSachPhong[j].getTrangThai() == 0) cout << setw(13) << "Chua dong |" << endl;
				else cout << setw(13) << "Da dong |" << endl;
				kt = true;
			}
		}
	}
	if (kt) cout << "\t\t\t------------------------------------------------------------------------------" << endl;
	else cout << "\t\t\t\t\tTat ca cac phong da dong tien dien!" << endl;
}

float KTX::TraCuuTienDien(int thuTuDay, int thuTuPhong) {
	return DsDay[thuTuDay].TraCuuTienDien(thuTuDay, thuTuPhong);
}
bool KTX::TraCuuTrangThaiTienDien(int thuTuDay, int thuTuPhong) {
	return DsDay[thuTuDay].TraCuuTrangThaiTienDien(thuTuDay, thuTuPhong);
}

void KTX::ThanhToanTienDien() {
	string mssv, tenDay, tenPhong, choice;
	float soTien;
	cout << "\n\t\t\t\t\t---Nhap thong tin---" << endl;
	do {
		cout << "\t\t\t\t\t->Nhap MSSV: ";
		getline(cin, mssv);
		if (mssv.size() != 10 or CoDauCach(mssv)) cout << "\t\t\t\t\tMSSV khong hop le!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
	} while (mssv.size() != 10 or CoDauCach(mssv));
	do {
		cout << "\t\t\t\t\t->Nhap ten day: ";
		getline(cin, tenDay);
		if (tenDay != "D1" and tenDay != "D2" and tenDay != "N1" and tenDay != "N2") {
			cout << "\t\t\t\t\tTen day da nhap khong dung!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl;
			cout << "\t\t\t\t\t[D1, D2, N1, N2]" << endl;
		}
	} while (tenDay != "D1" and tenDay != "D2" and tenDay != "N1" and tenDay != "N2");

	do {
		cout << "\t\t\t\t\t->Nhap ten phong: ";
		getline(cin, tenPhong);
		if (tenPhong != "P01" and tenPhong != "P02" and tenPhong != "P03" and tenPhong != "P04") {
			cout << "\t\t\t\t\tTen phong da nhap khong dung!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl;
			cout << "\t\t\t\t\t[P01, P02, P03, P04]" << endl;
		}
	} while (tenPhong != "P01" and tenPhong != "P02" and tenPhong != "P03" and tenPhong != "P04");
	//kiem tra mssv
	
	vector<Phong> danhSachPhong = DsDay[TenDayInt(tenDay)].getDsPhong();
	bool kt = danhSachPhong[TenPhongInt(tenPhong)].KiemTraMSSV(mssv);
	if (kt == false) {//ton tai mssv

		cout << endl << "\t\t\t\t\t" << tenDay << "-" << tenPhong << "\t Tien dien: " << TraCuuTienDien(TenDayInt(tenDay), TenPhongInt(tenPhong)) << "\tTrang thai: ";
		if (TraCuuTrangThaiTienDien(TenDayInt(tenDay), TenPhongInt(tenPhong)) == 0) {
			cout << "Chua dong" << endl;
		}
		else {
			cout << "Da dong" << endl;
			cout << "\t\t\t\t\tPhong cua ban da dong tien roi" << endl;
			return;
		}

		do {
			cout << "\t\t\t\t\t->Nhap so tien: ";
			cin >> soTien; cin.ignore();
			if (soTien != TraCuuTienDien(TenDayInt(tenDay), TenPhongInt(tenPhong)))
				cout << "\t\t\t\t\tSo tien da nhap khong dung!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
		} while (soTien != TraCuuTienDien(TenDayInt(tenDay), TenPhongInt(tenPhong)));

		do {
			cout << "\t\t\t\t\tNhan [y] de xac nhan giao dich hoac [n] de huy: ";
			getline(cin, choice);
			if (choice != "y" and choice != "n") cout << "\t\t\t\t\tCu phap khong dung!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
		} while (choice != "y" and choice != "n");

		if (choice == "n") {
			cout << "\t\t\t\t\tDa huy giao dich" << endl;
			return;
		};

		DsDay[TenDayInt(tenDay)].ThanhToanTienDien(TenPhongInt(tenPhong));
		vector<Phong>* danhSachPhongPtr = DsDay[TenDayInt(tenDay)].getDsPhongPtr();
		danhSachPhongPtr->at(TenPhongInt(tenPhong)).setTrangThai(true);
		cout << "\t\t\t\t\tThanh toan thanh cong!" << endl << endl;
	}
	else {
		cout << "\t\t\t\t\tMSSV khong co trong phong";
	}
}

void KTX::DangKySV() {
	SinhVien sv;
	cout << "\t\t\t\t\t<Luu y: Viet hoa chu cai dau>" << endl << endl;
	sv.Nhap();
	if (!(KiemTraMSSV(sv.getMSSV()))) {
		cout << "\t\t\t\t\tMSSV da nhap khong hop le hoac da trung!";
		return;
	}
	if (!(sv.KiemTraKhoa())) {
		return;
	}
	int dem = 0;
	cout << "\t\t\t\t\tDanh sach phong con trong:" << endl;
	XuatDsPhongTrong(sv.getGioiTinh(), dem);
	if (dem == 0) {
		cout << endl << "\t\t\t\t\tKhong the them sinh vien vao KTX!" << endl;
		return;
	}

	string thuTuDayStr, thuTuPhongStr;
	int thuTuDay, thuTuPhong;
	do {
		cout << "\n\t\t\t\t\tNhap ten day: ";
		cin >> thuTuDayStr; cin.ignore();
		cout << "\t\t\t\t\tNhap ten phong: ";
		cin >> thuTuPhongStr; cin.ignore();
		thuTuDay = TenDayInt(thuTuDayStr);
		thuTuPhong = TenPhongInt(thuTuPhongStr);
		if ((thuTuDay < 0 or thuTuDay>3) and (thuTuPhong < 0 or thuTuPhong>3)) cout << "\t\t\t\t\tDay va phong da nhap khong hop le!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
	} while (((thuTuDay < 0 or thuTuDay>3) and (thuTuPhong < 0 or thuTuPhong>3)));

	if (!KiemTraPhongTrong(thuTuDay, thuTuPhong, sv.getGioiTinh())) {
		cout << "\t\t\t\t\tPhong da day hoac thong tin nhap vao khong hop le!" << endl << endl;
		return;
	}
	else {
		ofstream file("DangKySV.txt", ios::app);
		if (!file.is_open()) {
			cout << "\t\t\t\t\tKhong the mo file dang ky!" << endl;
		}
		file << sv.getHoTen() << ",";
		file << sv.getMSSV() << ",";
		file << sv.getDiaChi() << ",";
		file << sv.getLop() << ",";
		file << sv.getKhoa() << ",";
		file << sv.getGioiTinh() << ",";
		file << sv.getSDT() << ",";
		Date ngaySinh = sv.getNgaySinh();
		file << ngaySinh.getNgay() << ",";
		file << ngaySinh.getThang() << ",";
		file << ngaySinh.getNam() << ",";
		file << TenDayInt(thuTuDayStr) << ",";
		file << TenPhongInt(thuTuPhongStr) << endl;;
		cout << "\t\t\t\t\tDa dang ky thanh cong!" << endl;
		file.close();
	}
}
void KTX::DuyetSV() {
	ifstream file("DangKySV.txt");

	if (!file.is_open()) 
		cout << "\t\t\t\t\tKhong the mo danh sach dang ky sinh vien!" << endl;

	if (file.peek() == ifstream::traits_type::eof()) 
		cout << "\t\t\t\t\tKhong co sinh vien dang ky" << endl;
	else cout << endl << "\t\t\t\t\t--- Thong tin sinh vien ---" << endl;
	{

		// Đọc 3 byte đầu tiên để kiểm tra BOM
		char bom[3] = { 0 };
		file.read(bom, 3);
		// Kiểm tra nếu file có BOM (UTF-8 BOM: EF BB BF)
		if (bom[0] != '\xEF' || bom[1] != '\xBB' || bom[2] != '\xBF') {
			// Không phải BOM, quay lại từ đầu
			file.seekg(0);
		}
		string line;
		while (getline(file, line)) {
			string hoTen, mssv, lop, khoa, diaChi, gioiTinh, sdt;
			int ngay, thang, nam, thuTuDay, thuTuPhong;
			stringstream ss(line);

			getline(ss, hoTen, ',');
			getline(ss, mssv, ',');
			getline(ss, diaChi, ',');
			getline(ss, lop, ',');
			getline(ss, khoa, ',');
			getline(ss, gioiTinh, ',');
			getline(ss, sdt, ',');
			ss >> ngay; ss.ignore();
			ss >> thang; ss.ignore();
			ss >> nam; ss.ignore();
			ss >> thuTuDay; ss.ignore();
			ss >> thuTuPhong; ss.ignore();

			Date ngaySinh(ngay, thang, nam);
			SinhVien sv(hoTen, mssv, diaChi, lop, khoa, gioiTinh, sdt, ngaySinh);
			cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
			cout << "|" << setw(7) << "Day |" << setw(9) << "Phong |" << setw(22) << "Ho ten |" << setw(15) << "MSSV |" << setw(13) << "Lop |" << setw(9) << "Khoa |" << setw(17) << "Dia Chi |" << setw(10) << "GTinh |" << setw(15) << "SDT |" << setw(16) << "Ngay sinh |\n";
			cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
			cout << "|" << setw(5) << ThuTuDayStr(thuTuDay) << " |" << setw(7) << ThuTuPhongStr(thuTuPhong) << " |";
			sv.XuatBang();
			cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
			if (!KiemTraPhongTrong(thuTuDay, thuTuPhong, gioiTinh)) {
				cout << "Phong da day! Khong the them vao KTX!" << endl << endl;
			}
			else {
				string choice;
				do {
					cout << "Nhan [y] de duyet hoac [n] de tu choi: ";
					getline(cin, choice);
					if (choice != "y" and choice != "n") cout << "Lua chon khong hop le! Vui long nhap lai!" << endl << endl;
				} while (choice != "y" and choice != "n");

				if (choice == "y") {
					ThemSinhVien(sv, thuTuDay, thuTuPhong);
					cout << "Them sinh vien thanh cong" << endl << endl;
				}
				else {
					cout << "Da tu choi sinh vien" << endl << endl;
				}
			}
		}
		file.close();
		ofstream XoaNoiDung("DangKySV.txt", ofstream::out | ofstream::trunc);
		XoaNoiDung.close();
	}
}
	

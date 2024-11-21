#include "SinhVien.h"
SinhVien::SinhVien() {
    HoTen = "";
    MSSV = "";
    DiaChi = "";
    Lop = "";
    Khoa = "";
    GioiTinh = "";
    SDT = "";
    NgaySinh = Date();
}

SinhVien::SinhVien(string hoTen, string mssv, string diaChi, string lop, string khoa, string gioiTinh, string sdt, Date ngaySinh)
    : HoTen(hoTen), MSSV(mssv), DiaChi(diaChi), Lop(lop), Khoa(khoa), GioiTinh(gioiTinh), SDT(sdt), NgaySinh(ngaySinh) {}

void SinhVien::setHoTen(string hoTen) { HoTen = hoTen; }
void SinhVien::setMSSV(string mssv) { MSSV = mssv; }
void SinhVien::setDiaChi(string diaChi) { DiaChi = diaChi; }
void SinhVien::setLop(string lop) { Lop = lop; }
void SinhVien::setKhoa(string khoa) { Khoa = khoa; }
void SinhVien::setGioiTinh(string gioiTinh) { GioiTinh = gioiTinh; }
void SinhVien::setSDT(string sdt) { SDT = sdt; }
void SinhVien::setNgaySinh(Date ngaySinh) { NgaySinh = ngaySinh; }

string SinhVien::getHoTen() { return HoTen; }
string SinhVien::getMSSV() { return MSSV; }
string SinhVien::getDiaChi() { return DiaChi; }
string SinhVien::getLop() { return Lop; }
string SinhVien::getKhoa() { return Khoa; }
string SinhVien::getGioiTinh() { return GioiTinh; }
string SinhVien::getSDT() { return SDT; }
Date SinhVien::getNgaySinh() { return NgaySinh; }
string SinhVien::getTen() {
    stringstream ss(HoTen);
    string ten;
    vector<string> tenList;
    while (ss >> ten) {
        tenList.push_back(ten);
    }
    return tenList.back();
}

void SinhVien::Nhap() {
    cout << "\t\t\t\t\tNhap ho ten: ";
    getline(cin, HoTen);
    do {
        cout << "\t\t\t\t\tNhap MSSV: ";
        getline(cin, MSSV);
        if (MSSV.size() != 10 or CoDauCach(MSSV)) cout << "\t\t\t\t\tMSSV khong hop le!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
    } while (MSSV.size() != 10 or CoDauCach(MSSV));

    cout << "\t\t\t\t\tNhap dia chi: ";
    getline(cin, DiaChi);
    cout << "\t\t\t\t\tNhap lop: ";
    getline(cin, Lop);

    cout << "\t\t\t\t\tNhap khoa [Kxx]: ";
    getline(cin, Khoa);


    do {
        cout << "\t\t\t\t\tNhap gioi tinh: ";
        getline(cin, GioiTinh);
        if (GioiTinh != "Nam" and GioiTinh != "Nu") cout << "\t\t\t\t\tGioi tinh khong hop le!" << endl << "\t\t\t\t\tVui long nhap lai! [Nam/Nu]" << endl << endl;
    } while (GioiTinh != "Nam" and GioiTinh != "Nu");

    do {
        cout << "\t\t\t\t\tNhap so dien thoai: ";
        getline(cin, SDT);
        if (SDT.size() != 10 or !kiemTraSDT(SDT)) cout << "\t\t\t\t\tSDT khong hop le!" << endl << "\t\t\t\t\tVui long nhap lai!" << endl << endl;
    } while (SDT.size() != 10 or !kiemTraSDT(SDT));
    NgaySinh.Nhap();
    cin.ignore();  // Để bỏ qua ký tự xuống dòng sau khi nhập số
}

void SinhVien::XuatDonGian() {
    cout << setw(23) << HoTen << " |" << setw(18) << MSSV << " |" << setw(13) << Lop << " |" << setw(8) << Khoa << " |" << endl;;
}

void SinhVien::XuatBang() {
    cout << setw(20) << HoTen << " |" << setw(13) << MSSV << " |" << setw(11) << Lop << " |" << setw(7) << Khoa << " |" << setw(15) << DiaChi << " |" << setw(8) << GioiTinh << " |" << setw(13) << SDT << " |   ";
    NgaySinh.Xuat();
    cout << " |" << endl;
}
bool SinhVien::KiemTraKhoa() {
    if (!(Khoa == "K65" or Khoa == "K64" or Khoa == "K63" or Khoa == "K62")) {
        cout << "\t\t\t\t\tKhoa da nhap khong hop le hoac vuot qua khoa quy dinh cua KTX";
        return false;
    }
    return true;
}

bool SinhVien::TimSinhVienTheoTen(string ten) {
    return getTen() == ten;
}


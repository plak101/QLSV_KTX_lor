#include <iostream>
#include <vector>
#include <string>
#include <dos.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Date.h"
#include "Day.h"
#include "KTX.h"
#include "Phong.h"
#include "SinhVien.h"
#include "XuLiChuoi.h"
#include "XuLi.h"
using namespace std;
int main() {
	KTX ktx;
	Begin(ktx);
	XoaManHinh();
	menu(ktx);
}
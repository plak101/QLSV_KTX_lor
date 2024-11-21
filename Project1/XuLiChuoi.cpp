#include "XuLiChuoi.h"
bool CoDauCach(string chuoi) {
    for (char kyTu : chuoi) {
        if (kyTu == ' ') {
            return true;
        }
    }
    return false;
}
bool kiemTraSDT(string  sdt) {
    for (char kyTu : sdt) 
        if (!isdigit(kyTu)) return false ;
    return true;
}
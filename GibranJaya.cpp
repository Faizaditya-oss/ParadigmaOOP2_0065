#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class RekeningBank {
protected:
    string namaNasabah;
    string nomorRekening;
    double saldo;

public:
    RekeningBank(string nama, string noRek, double saldoAwal) {
        namaNasabah    = nama;
        nomorRekening  = noRek;
        saldo          = saldoAwal;
    }
    virtual void potongAdmin() = 0;
    virtual string getJenis() = 0;
    virtual ~RekeningBank() {}


    string getNama()  { return namaNasabah; }
    string getNoRek() { return nomorRekening; }
    double getSaldo() { return saldo; }

   
    void tampilInfo() {
        cout << fixed << setprecision(0);
        cout << "  Nama     : " << namaNasabah    << endl;
        cout << "  No. Rek  : " << nomorRekening  << endl;
        cout << "  Jenis    : " << getJenis()      << endl;
        cout << "  Saldo    : Rp " << saldo        << endl;
    }
};



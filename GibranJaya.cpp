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

class RekeningySyariah : public RekeningBank {

public:
    RekeningySyariah(string nama, string noRek, double saldoAwal)
        : RekeningBank(nama, noRek, saldoAwal) {
    }
    void potongAdmin() override {
        cout << "  [INFO] Rekening Syariah - bebas biaya admin!" << endl;
        cout << "  Saldo tetap: Rp " << saldo << endl;
    }

    string getJenis() override {
        return "Rekening Syariah";
    }
};

class RekeningKonvensional : public RekeningBank {

private:
    static const double BIAYA_ADMIN; 

public:
    RekeningKonvensional(string nama, string noRek, double saldoAwal)
        : RekeningBank(nama, noRek, saldoAwal) {}

    void potongAdmin() override {
        if (saldo >= BIAYA_ADMIN) {
            saldo = saldo - BIAYA_ADMIN; 
            cout << "  [POTONG] Biaya admin Rp " << BIAYA_ADMIN << " berhasil dipotong." << endl;
        } else {
            cout << "  [GAGAL] Saldo kurang! Minimal harus ada Rp " << BIAYA_ADMIN << endl;
        }
        cout << "  Saldo sekarang: Rp " << saldo << endl;
    }

    string getJenis() override {
        return "Rekening Konvensional";
    }
};

// Nilai static diluar class
const double RekeningKonvensional::BIAYA_ADMIN = 15000.0;

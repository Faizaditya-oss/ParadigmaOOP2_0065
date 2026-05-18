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
class RekeningPremium : public RekeningBank {

private:
    static const double BATAS_GRATIS;
    static const double BIAYA_ADMIN_PREMIUM;

public:
    RekeningPremium(string nama, string noRek, double saldoAwal)
        : RekeningBank(nama, noRek, saldoAwal) {}

    void potongAdmin() override {
        if (saldo > BATAS_GRATIS) {
            cout << "  [BEBAS] Saldo di atas Rp " << BATAS_GRATIS;
            cout << " jadi gratis admin!" << endl;
            cout << "  Saldo tetap: Rp " << saldo << endl;

        } else {
            cout << "  [INFO] Saldo <= Rp " << BATAS_GRATIS;
            cout << ", kena biaya admin Rp " << BIAYA_ADMIN_PREMIUM << endl;

            if (saldo >= BIAYA_ADMIN_PREMIUM) {
                saldo -= BIAYA_ADMIN_PREMIUM;
                cout << "  [POTONG] Berhasil dipotong." << endl;
            } else {
                cout << "  [GAGAL] Saldo ga cukup buat bayar admin!" << endl;
            }
            cout << "  Saldo sekarang: Rp " << saldo << endl;
        }
    }

    string getJenis() override {
        return "Rekening Premium";
    }
};

// Nilai konstanta
const double RekeningPremium::BATAS_GRATIS        = 10000000.0; // 10 juta
const double RekeningPremium::BIAYA_ADMIN_PREMIUM  =    50000.0; // 50 ribu


void cetakGaris() {
    cout << setfill('=') << setw(50) << "" << setfill(' ') << endl;
}

int main() {
    vector<RekeningBank*> daftarRekening;
    
    daftarRekening.push_back(new RekeningySyariah    ("Ahmad Fauzi",   "SYR-001", 5000000));
    daftarRekening.push_back(new RekeningySyariah    ("Siti Rahayu",   "SYR-002", 200000));
    daftarRekening.push_back(new RekeningKonvensional("Budi Santoso",  "KON-001", 2500000));
    daftarRekening.push_back(new RekeningKonvensional("Dewi Lestari",  "KON-002", 10000));  // saldo tipis
    daftarRekening.push_back(new RekeningPremium     ("Hendra Wijaya", "PRM-001", 15000000)); // sultan
    daftarRekening.push_back(new RekeningPremium     ("Rina Kusuma",   "PRM-002", 8000000));
    daftarRekening.push_back(new RekeningPremium     ("Joko Susilo",   "PRM-003", 30000));   // kasian

    
    cetakGaris();
    cout << "   BANK GIBRAN JAYA - PROSES AKHIR BULAN" << endl;
    cetakGaris();
    for (int i = 0; i < daftarRekening.size(); i++) {
        cout << "\n[Rekening ke-" << (i + 1) << "]" << endl;
        daftarRekening[i]->tampilInfo();
        cout << "  -- Proses potongan: --" << endl;
        daftarRekening[i]->potongAdmin();
    }

   
    cout << "\n";
    cetakGaris();
    cout << "   RINGKASAN SALDO AKHIR" << endl;
    cetakGaris();

    cout << left; 
    cout << setw(18) << "Nama"
         << setw(24) << "Jenis Rekening"
         << "Saldo Akhir" << endl;
    cout << setfill('-') << setw(55) << "" << setfill(' ') << endl;

    for (int i = 0; i < daftarRekening.size(); i++) {
        cout << fixed << setprecision(0);
        cout << setw(18) << daftarRekening[i]->getNama()
             << setw(24) << daftarRekening[i]->getJenis()
             << "Rp " << daftarRekening[i]->getSaldo()
             << endl;
    }

    cetakGaris();
    for (int i = 0; i < daftarRekening.size(); i++) {
        delete daftarRekening[i];
    }

    daftarRekening.clear();

    cout << "\nProgram selesai! Semoga nilainya bagus :)" << endl;

    return 0; 
}
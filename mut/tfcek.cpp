#include <iostream>
#include <string>
using namespace std;

// Struktur data untuk menyimpan informasi akun
struct Akun {
    string nomorKartu; // Nomor kartu akun
    int saldo; // Saldo akun
    Akun* next; // Pointer ke akun berikutnya
};

// Struktur data untuk menyimpan informasi transaksi
struct Transaksi {
    string nomorKartu; // Nomor kartu penerima transfer
    string jenisTransaksi; // Jenis transaksi (transfer, cek saldo, dll)
    string jumlah; // Jumlah uang yang terlibat dalam transaksi
    Transaksi* next; // Pointer ke transaksi berikutnya
};

// Method untuk membuat akun baru
void buatAkun(Akun*& head, string nomorKartu, int saldo) {
    Akun* baru = new Akun;
    baru->nomorKartu = nomorKartu;
    baru->saldo = saldo;
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Akun* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

// Method untuk melakukan transfer
void transfer(Transaksi*& head, string nomorKartu, string jumlah) {
    // Simulasi proses transfer
    cout << "====================================================" << endl;
    cout << "Transaksi sebesar " << jumlah << " ke nomor kartu " << nomorKartu << " berhasil dilakukan." << endl;
}

// Method untuk menambahkan transaksi baru ke akhir histori
void tambahTransaksi(Transaksi*& head, string jenis, string jumlah) {
    Transaksi* baru = new Transaksi;
    baru->jenisTransaksi = jenis;
    baru->jumlah = jumlah;
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Transaksi* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

// Method untuk mencetak histori transaksi
void cetakHistori(Transaksi* head) {
    Transaksi* temp = head;
    while (temp != NULL) {
        cout << "Jenis: " << temp->jenisTransaksi << ", Jumlah: " << temp->jumlah << endl;
        temp = temp->next;
    }
}

// Method untuk menghitung sisa saldo
int cekSaldo(Akun* head, string nomorKartu) {
    Akun* temp = head;
    while (temp != NULL) {
        if (temp->nomorKartu == nomorKartu) {
            return temp->saldo;
        }
        temp = temp->next;
    }
    return 0; // Jika nomor kartu tidak ditemukan
}

int main() {
    Akun* daftarAkun = NULL; // Inisialisasi daftar akun
    Transaksi* historiTransaksi = NULL; // Inisialisasi histori transaksi

    // Membuat beberapa akun untuk uji coba
    buatAkun(daftarAkun, "123456", 1000);
    buatAkun(daftarAkun, "789012", 2000);

    char pilihan;
    bool loggedIn = true;
    string nomorKartu;
    int saldoUser = 0; // Inisialisasi saldo awal user

    // Meminta pengguna memasukkan nomor kartu untuk login
    cout << "Masukkan nomor kartu Anda: ";
    cin >> nomorKartu;

    // Mencari saldo user saat login
    saldoUser = cekSaldo(daftarAkun, nomorKartu);

    // Loop menu
    while (loggedIn) {
        // Meminta pengguna memilih menu
        cout << "Pilihan menu:" << endl;
        cout << "a. Transfer" << endl;
        cout << "b. Cek Saldo" << endl;
        cout << "c. Logout" << endl;
        cout << "Pilih menu (a/b/c): ";
        cin >> pilihan;

        if (pilihan == 'a') {
            // Input nomor kartu penerima dan jumlah transfer
            string nomorKartuPenerima;
            string jumlahTransfer;
            cout << "===================== TRANSFER ====================" << endl;
            cout << "Masukkan nomor kartu penerima: ";
            cin >> nomorKartuPenerima;
            cout << "Masukkan jumlah transfer: ";
            cin >> jumlahTransfer;

            // Melakukan transfer
            transfer(historiTransaksi, nomorKartuPenerima, jumlahTransfer);

            // Menambahkan transaksi transfer ke dalam histori
            tambahTransaksi(historiTransaksi, "Transfer", jumlahTransfer);
        } else if (pilihan == 'b') {
            // Menampilkan sisa saldo
            cout << "===================== CEK SALDO ====================" << endl;
            cout << "Sisa saldo Anda: " << saldoUser << endl;
            cout << "====================================================" << endl;
        } else if (pilihan == 'c') {
            cout << "Anda telah logout." << endl;
            loggedIn = false;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}

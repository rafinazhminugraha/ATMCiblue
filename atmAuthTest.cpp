#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// hierarcial struct used to pack transaction data
struct TRANSAKSI {
    int nominal;
    string kategori;
    string keteranganWaktu;
};

// double linked list struct
struct NASABAH {
    string nama;
    string pin;
    string nomorKartu;
    int jumlahSaldo;
    vector<TRANSAKSI> riwayatTransaksi;
    NASABAH *prev;
    NASABAH *next;
};

NASABAH *head;
NASABAH *tail;

bool kosong() {
    if (head == NULL) {
        return true;
    } return false;
}

void tambahAkun(string nama, string pin, string nomorKartu) {
    NASABAH *nodeBaru;
    nodeBaru = new NASABAH;
    nodeBaru->nama = nama;
    nodeBaru->pin = pin;
    nodeBaru->nomorKartu = nomorKartu;
    nodeBaru->jumlahSaldo = 0;

    if (kosong()) {
        head = nodeBaru;
        head -> next = NULL;
    } else {
        nodeBaru -> next = head;
        nodeBaru -> prev = NULL;
        head = nodeBaru;
    }
}

void hapusAkun() {
    NASABAH *hapus, *current;
    string nama, pin, nomorKartu;

    if (kosong()) {
        head = NULL;
    } else if (head->next == NULL) {
        hapus = head;
        head = NULL; tail = NULL;
        delete hapus;
    } else {
        current = head;
        while (current->next->next != NULL) {
            current = current->next;
        } delete current->next;

        current->next = NULL;
        tail = current;
    }
}

void hapusBaris(int baris) {
    if (baris > 0) {
        cout << "\x1b[2K";
        for (int i = 1; i < baris; i++) {
            cout << "\x1b[1A" << "\x1b[2K";
        } cout << "\r";
    }
}

string kapital(string kata, bool kapital, bool judul) {
    if ((kapital || !kapital) && judul) {
        for (int i = 0; i < kata.length(); i++) {
            kata[0] = toupper(kata[0]);

            if (kata[i] == ' ') {
                kata[i + 1] = toupper(kata[i + 1]);
            }
        }
    } else if (!kapital) {
        for (int i = 0; i < kata.length(); i++) {
            kata[i] = tolower(kata[i]);
        }
    } else {
        for (int i = 0; i < kata.length(); i++) {
            kata[i] = toupper(kata[i]);
        }
    } return kata;
}

int cekString(string str, bool isDigit, char spesial = '<') {
    for (int i = 0; i < str.length(); i++) {
        if (isDigit) {
            if (str[i] == spesial) {
                return 1;
            }
            else if (isdigit(str[i]) == false && str[i] != ' ') {
                return 2;
            }
        } else {
            if (str[i] == spesial) {
                return 1;
            }
            else if (isalpha(str[i]) == false && str[i] != ' ') {
                return 2;
            }
        }
    } return 0;
}

string buatNomorRandom(int panjang) {
    NASABAH *current;
    current = head;

    string nomor = "";
    srand(time(0));
    
    for (int i = 0; i < panjang; i++) {
        nomor += to_string(rand() % 9);
    } while (current != NULL) {
        if (nomor == current->nomorKartu) {
            buatNomorRandom(panjang);
        } current = current->next;
    } return nomor;
}

void tampilkanTransaksi(NASABAH* nasabah) {
    if (nasabah != nullptr) {
        cout << "Riwayat Transaksi: " << endl;
        for (const TRANSAKSI& transaksi : nasabah->riwayatTransaksi) {
            cout << transaksi.keteranganWaktu << endl;
            cout << "Nominal: Rp" << transaksi.nominal << endl;
            cout << "Kategori: " << transaksi.kategori << endl;
            cout << "-------------------------" << endl;
        }
    } else {
        cout << "NODE Nasabah == NULL";
    }
}

void tampilkanNasabah() {
    system("cls");

    if (!kosong()) {
        NASABAH *current;
        current = head;
        int nomor = 1;

        while (current != NULL) {
            cout << "[" << nomor << "]" << endl;
            cout << "Nama: " << kapital(current->nama, true, true) << endl;
            cout << "PIN: " << current->pin << endl;
            cout << "Nomor Kartu: " << current->nomorKartu << endl;
            cout << "Jumlah Saldo: Rp" << current->jumlahSaldo << endl << endl;

            tampilkanTransaksi(current);

            current = current->next;
            nomor += 1;
        } cout << endl;
    } else {
        cout << "Belum ada nasabah yang terdaftar." << endl;
    } system("pause");
}


void peringatan(string teks, bool jeda = true, bool bersihkan = true, bool back = false) {
    cout << endl << teks;
    if (jeda) {
        cout << endl;
        system("pause");
    } if (back) {
        cout << endl << endl;
    } if (bersihkan) {
        system("cls");
    }
}

void tampilkanHeader(string teks[], int baris, string simbol, int karakter) {
    system("cls");

    int maks = karakter;
    int panjangSimbol = simbol.length();
    char simbolTunggal[panjangSimbol] = {};

    for (int i = 0; i < panjangSimbol; i++) {
        simbolTunggal[i] = simbol[i];
    }
    
    for (int i = 0; i < baris; i++) {
        int banyakSimbol = ((maks - 2 - teks[i].length()) / 2);
        teks[i] = kapital(teks[i], true, false); 

        if (banyakSimbol > 0) {
            string kiri = ""; string kanan = " ";

            for (int j = 0; j < banyakSimbol; j++) {
                kiri += simbolTunggal[j % panjangSimbol];
            } kiri += " ";

            for (int j = 0; j < banyakSimbol; j++) {
                kanan += simbolTunggal[j % panjangSimbol];
            }

            if (teks[i].length() % 2 != 0) {
                int indeks;
                if (panjangSimbol % 2 != 0) {
                    indeks = i % panjangSimbol;
                } else {
                    indeks = i & panjangSimbol - 1;
                } kanan += simbolTunggal[indeks];
            } cout << kiri << teks[i] << kanan << endl;
        } else {
            cout << "Terlalu Panjang!" << endl;
        } 
    } cout << endl;
}

string menu(string opsi[], int banyak, bool bersihkan) {
    string inputOpsi;
    if (bersihkan) {
        system("cls");
    }
    for (int i = 0; i < banyak; i++) {
        opsi[i] = kapital(opsi[i], true, true);
        cout << "[" << i + 1 << "] " << opsi[i] << endl;
    } cout << endl << "Opsi: "; cin >> inputOpsi;

    return inputOpsi;
}

NASABAH* cariNasabahKartu(NASABAH *head, string nomorKartu) {
    NASABAH* current = head;

    while (current != nullptr) {
        if (nomorKartu == current->nomorKartu) {
            return current;
        } current = current->next;
    } return nullptr;
}

NASABAH* cariNasabahNama(NASABAH *head, string nama) {
    NASABAH* current = head;

    while (current != nullptr) {
        if (nama == current->nama) {
            return current;
        } current = current->next;
    } return nullptr;
}

void tambahTransaksi(NASABAH *nasabah, int nominal, string keterangan) {
    if (nasabah != nullptr) {
        TRANSAKSI transaksiBaru;
        transaksiBaru.nominal = nominal;
        transaksiBaru.kategori = keterangan;

        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt) - 1] = '\0';
        transaksiBaru.keteranganWaktu = string(dt);

        nasabah->riwayatTransaksi.push_back(transaksiBaru);
    }
}

void ubahSaldo(NASABAH* nasabah, int nominal, bool isTambah) {
    if (nasabah != nullptr) {
        if (isTambah) {
            nasabah->jumlahSaldo += nominal;
            tambahTransaksi(nasabah, nominal, "SETOR TUNAI");
        } else {
            nasabah->jumlahSaldo -= nominal;
            tambahTransaksi(nasabah, nominal, "TRANSFER");
        }
    } else {
        cout << "NODE Nasabah == NULL";
    }
}

int masuk(string nomorKartu, string pin) {
    NASABAH *current;
    current = head;

    // linear search
    while (current != NULL) {
        // three possible ouput used to represent loggedin, wrong pin, and not registered
        if (nomorKartu == current->nomorKartu && pin == current -> pin) {
            return 0;
        } else if (nomorKartu == current->nomorKartu && pin != current->pin) {
            return 1;
        } current = current->next;
    } return 2;
}

bool isUseExist(string nama, string nomorKartu) {
    NASABAH *current;
    current = head;

    while (current != NULL) {
        if (nama == current->nama && nomorKartu == current->nomorKartu) {
            return true;
        } current = current->next;
    } return false;
}

bool daftar(string nama, string pin) {
    string nomorKartu = "000" + buatNomorRandom(3);
    
    // register new user if not registered yet (based on its nama)
    if (!isUseExist(nama, nomorKartu)) {
        tambahAkun(nama, pin, nomorKartu);
        return false;
    } else {
        return true;
    }
}

int main() {
    NASABAH *nasabah;
    string namaMasuk, pinMasuk, kartuMasuk;
    string namaDaftar, pinDaftar, kartuDaftar;
    int saldoAwalDaftar;
    int limit = 3;
    int isLoggedin;
    bool isRegistered;
    bool isNamaAlpha; bool namaLimit; bool kartuLimit;
    bool isPinDigit; bool pinLimit; bool isKartuDigit;
    bool isSaldoAwalDigit; bool saldoAwalLimit;

    string selamatDatang[] = {"selamat datang", "di atm kantongku"};
    string headerMasuk[] = {"menu", "masuk"};
    string opsiMasuk[] = {"nama", "nomor kartu"};
    string headerDaftar[] = {"menu", "daftar"};
    string headerTampilanNasabah[] = {"tampilan", "daftar nasabah"};
    string opsiMenuUtama[] = {"masuk", "daftar", "tampilkan nasabah", "keluar"};

    while (true) {
        programUtama:
            tampilkanHeader(selamatDatang, 2, "#=#=", 32);

            string opsi = menu(opsiMenuUtama, 4, false);

            if (opsi == "1") {
                goto menuMasuk;
            } else if (opsi == "2") {
                goto menuDaftar;
            } else if (opsi == "3") {
                goto menuDaftarNasabah;
            } else if (opsi == "4") {
                goto menuKeluar;
            } else {
                goto menuTidakValid;
            } 

            menuMasuk:
                while (true) {
                    tampilkanHeader(headerMasuk, 2, "#=#=", 32);
                    peringatan("Input (<) untuk KEMBALI", false, false, true);

                        while (true) {
                            opsi = menu(opsiMasuk, 2, false);
                            hapusBaris(5);
                            
                            if (opsi == "1") {
                                goto inputNamaMasuk;
                            } else if (opsi == "2") {
                                 goto inputNomorMasuk;
                            } else if (opsi == "<") {
                                goto programUtama;
                            } else {
                                peringatan("Input tidak valid!");
                                break;
                            }
                        } continue;

                    inputNamaMasuk:
                        while (true) {
                            cout << "Nama: "; cin.ignore(); getline(cin, namaMasuk);
                            namaMasuk = kapital(namaMasuk, false, false);

                            cekNamaMasuk:
                                isNamaAlpha = cekString(namaMasuk, false) == 0;
                                namaLimit = namaMasuk.length() >= 8;
                                
                                if (namaMasuk == "<") {
                                    goto menuMasuk;
                                } if (isNamaAlpha && namaLimit) {
                                    goto inputPinMasuk;
                                } if (!isNamaAlpha) {
                                    peringatan("Nama hanya terdiri dari huruf.", false, false);
                                } if (!namaLimit) {
                                    peringatan("Nama minimal terdiri dari 8 karakter.", false, false);
                                } cout << endl; system("pause");

                            tampilkanHeader(headerMasuk, 2, "#=#=", 32);
                            peringatan("Input (<) untuk KEMBALI", false, false, true);
                            cout << "Nama: "; getline(cin, namaMasuk);
                            namaMasuk = kapital(namaMasuk, false, false);
                            goto cekNamaMasuk;
                        }

                    inputNomorMasuk:
                        while (true) {
                            cout << "Nomor Kartu: "; cin >> kartuMasuk;

                            isKartuDigit = cekString(kartuMasuk, true) == 0;
                            kartuLimit = kartuMasuk.length() == 6;
                            
                            if (kartuMasuk == "<") {
                                goto menuMasuk;
                            } if (isKartuDigit && kartuLimit) {
                                goto inputPinMasuk;
                            } if (!isKartuDigit) {
                                peringatan("Nomor kartu hanya terdiri dari angka.", false, false);
                            } if (!kartuLimit) {
                                peringatan("Nomor kartu terdiri dari 6 digit.", false, false);
                            } cout << endl; system("pause");

                            tampilkanHeader(headerMasuk, 2, "#=#=", 32);
                            peringatan("Input (<) untuk KEMBALI", false, false, true);
                            continue;
                        }

                    inputPinMasuk:
                        while (limit > 0) {
                            cout << "PIN: "; cin >> pinMasuk;

                            isPinDigit = cekString(pinMasuk, true) == 0;
                            pinLimit = pinMasuk.length() == 6;

                            cekPinMasuk:
                                if (pinMasuk == "<") {
                                    goto menuMasuk;
                                } if (isPinDigit && pinLimit) {
                                    break;
                                } if (!isPinDigit) {
                                    peringatan("PIN hanya terdiri dari angka.", false, false);
                                } if (!pinLimit) {
                                    peringatan("PIN harus terdiri dari 6 digit.", false, false);
                                } cout << endl; system("pause");

                            tampilkanHeader(headerMasuk, 2, "#=#=", 32);
                            peringatan("Input (<) untuk KEMBALI", false, false, true);
                            if (opsi == "1") {
                                cout << "Nama: " << kapital(namaMasuk, true, true) << endl;
                            }
                            else if (opsi == "2") {
                                cout << "Nomor Kartu: " << kartuMasuk << endl;
                            }
                            continue;

                            inputPinMasukLoop:
                                tampilkanHeader(headerMasuk, 2, "#=#=", 32);
                                peringatan("Input (<) untuk KEMBALI", false, false, true);
                                if (opsi == "1") {
                                    cout << "Nama: " << kapital(namaMasuk, true, true) << endl;
                                } else if (opsi == "2") {
                                    cout << "Nomor Kartu: " << kartuMasuk << endl;
                                }
                                cout << "PIN: "; cin >> pinMasuk;
                                goto cekPinMasuk;
                        }
                    
                    if (opsi == "1") {
                        nasabah = cariNasabahNama(head, namaMasuk);
                        if (nasabah != nullptr) {
                            kartuMasuk = nasabah->nomorKartu;
                        } else {
                            goto verifyingMasuk;
                        }
                    } else if (opsi == "2") {
                        nasabah = cariNasabahKartu(head, kartuMasuk);
                        if (nasabah != nullptr) {
                            namaMasuk = nasabah->nama;
                        } else {
                            goto verifyingMasuk;
                        }
                    } verifyingMasuk: isLoggedin = masuk(kartuMasuk, pinMasuk);

                    if (isLoggedin == 0) {
                        // next step here
                        // good luck 👌
                        peringatan("Halo, " + kapital(namaMasuk, true, true) +  "!", false, false);
                        peringatan("Selamat datang di ATM Kantongku");
                        goto programUtama;
                    } else if (isLoggedin == 1) {
                        limit -= 1;
                        if (limit == 0) {
                            peringatan("Batas percobaan PIN telah terlampaui.");
                            goto programUtama;
                        }

                        peringatan("PIN yang Anda masukkan salah!", false, false);
                        peringatan("Batas percobaan " + to_string(limit) + "x lagi.");
                        goto inputPinMasukLoop;
                    } else if (isLoggedin == 2) {
                        peringatan("Belum terdaftar sebagai nasabah!", false, false);
                        peringatan("Menuju MENU DAFTAR...");
                        goto menuDaftar;
                    }
                    
                }

            menuDaftar:
                tampilkanHeader(headerDaftar, 2, "#=#=", 32);
                peringatan("Input (<) untuk KEMBALI", false, false, true);

                inputNamaDaftar:
                    while (true) {
                        cout << "Nama: "; cin.ignore(); getline(cin, namaDaftar); 
                        namaDaftar = kapital(namaDaftar, false, false);

                        cekNamaDaftar:
                            isNamaAlpha = cekString(namaDaftar, false) == 0;
                            namaLimit = namaDaftar.length() >= 8;

                            if (namaDaftar == "<") {
                                goto programUtama;
                            } else if (isNamaAlpha && namaLimit) {
                                break;
                            } else if (!isNamaAlpha) {
                                peringatan("Nama hanya terdiri dari huruf.", false, false);
                            } else if (!namaLimit) {
                                peringatan("Nama minimal terdiri dari 8 karakter.", false, false);
                            } cout << endl; system("pause");

                        tampilkanHeader(headerDaftar, 2, "#=#=", 32);
                        peringatan("Input (<) untuk KEMBALI", false, false, true);
                        cout << "Nama: "; getline(cin, namaDaftar); 
                        namaDaftar = kapital(namaDaftar, false, false);
                        goto cekNamaDaftar;
                    }

                inputPinDaftar:
                    while (true) {
                        cout << "PIN: "; cin >> pinDaftar;

                        isPinDigit = cekString(pinDaftar, true) == 0;
                        pinLimit = pinDaftar.length() == 6;

                        if (pinDaftar == "<") {
                            goto programUtama;
                        } if (isPinDigit && pinLimit) {
                            break;
                        } if (!isPinDigit) {
                            peringatan("PIN hanya terdiri dari angka.", false, false);
                        } if (!pinLimit) {
                            peringatan("PIN harus terdiri dari 6 digit.", false, false);
                        } cout << endl; system("pause");

                        tampilkanHeader(headerDaftar, 2, "#=#=", 32);
                        peringatan("Input (<) untuk KEMBALI", false, false, true);
                        cout << "Nama: " << kapital(namaDaftar, true, true) << endl;
                        continue;
                    }

                isRegistered = daftar(namaDaftar, pinDaftar);

                if (isRegistered) {
                    peringatan("Nasabah dengan nama ini sudah terdaftar!", false, false);
                    peringatan("Menuju ke MENU MASUK...");
                    goto menuMasuk;
                } else {
                    kartuDaftar = cariNasabahNama(head, namaDaftar)->nomorKartu;
                    cout << "Nomor Kartu: " << kartuDaftar << endl;
                }

                inputSaldoAwal:
                    while (true) {
                        string inputSaldoAwal;
                        cout << "Saldo Awal (min. Rp500000): Rp"; cin >> inputSaldoAwal;

                        isSaldoAwalDigit = cekString(inputSaldoAwal, true) == 0;
                        
                        if (inputSaldoAwal == "<") {
                            goto programUtama;
                        } if (isSaldoAwalDigit) {
                            saldoAwalDaftar = stoi(inputSaldoAwal);
                            saldoAwalLimit = saldoAwalDaftar >= 500000;
                            if (isSaldoAwalDigit && saldoAwalLimit) {
                                break;
                            } if (!saldoAwalLimit) {
                                peringatan("Nominal saldo awal minimal Rp500000.", false, false);
                            } 
                        } else {
                            peringatan("Input saldo awal harus berupa angka.", false, false);
                        } cout << endl; system("pause");

                        tampilkanHeader(headerDaftar, 2, "#=#=", 32);
                        peringatan("Input (<) untuk KEMBALI", false, false, true);
                        cout << "Nama: " << kapital(namaDaftar, true, true) << endl;
                        cout << "PIN: " << pinDaftar << endl;
                        cout << "Nomor Kartu: " << kartuDaftar << endl;
                        continue;
                    }
                
                ubahSaldo(cariNasabahKartu(head, kartuDaftar), saldoAwalDaftar, true);
                peringatan("Selamat datang nasabah baru!");
                goto programUtama;

            menuDaftarNasabah:
                tampilkanHeader(headerDaftar, 2, "#=#=", 32);
                tampilkanNasabah();
                continue;

            menuKeluar:
                peringatan("Terima kasih telah menggunakan ATM Kantongku", false, false);
                peringatan("Sampai jumpa :D");
                break;
            
            menuTidakValid:
                peringatan("Input tidak valid!");
                continue;
        } return 0;
}
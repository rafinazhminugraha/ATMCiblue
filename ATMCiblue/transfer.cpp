#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
using namespace std;


void printJudul() {
    cout << "\033[2J\033[1;1H";
    cout << "=============\n";
    cout << "     ATM     \n";
    cout << "=============\n";
}

// hierarcial struct used to pack transaction data
struct Transaksi {
    string keterangan;
    int jumlah;
    time_t waktu;
};

// double linked list struct
struct NASABAH {
    string nama;
    string pin;
    string nomorKartu;
    int jumlahSaldo;
    vector<Transaksi> riwayatTransaksi;
    NASABAH *prev;
    NASABAH *next;
};

struct NASABAH;

NASABAH *head;
NASABAH *tail;

bool kosong() {
    if (head == NULL) {
        return true;
    } return false;
}

NASABAH* cariNasabahTransfer(NASABAH* head, string nomorKartu) 
{
    NASABAH* temp = head;
    while (temp != nullptr) {
        if (temp->nomorKartu == nomorKartu) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void tambahAkun(string nama, string pin, string nomorKartu, int saldoAwal) 
{
    NASABAH *nodeBaru;
    nodeBaru = new NASABAH;
    nodeBaru->nama = nama;
    nodeBaru->pin = pin;
    nodeBaru->jumlahSaldo = saldoAwal;
    nodeBaru->nomorKartu = nomorKartu;

    if (kosong()) {
        head = nodeBaru;
        head -> next = NULL;
    } else {
        nodeBaru -> next = head;
        nodeBaru -> prev = NULL;
        head = nodeBaru;
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

// void tampilkanTransaksi(NASABAH* nasabah) {
//     if (nasabah != nullptr) {
//         cout << "Riwayat Transaksi: " << endl;
//         for (const Transaksi& transaksi : nasabah->riwayatTransaksi) {
//             cout << transaksi.waktu << endl;
//             cout << "Nominal: Rp" << transaksi.jumlah << endl;
//             cout << "Kategori: " << transaksi.keterangan << endl;
//             cout << "-------------------------" << endl;
//         }
//     } else {
//         cout << "NODE Nasabah == NULL";
//     }
// }

// void tampilkanNasabah() {
//     system("cls");

//     if (!kosong()) {
//         NASABAH *current;
//         current = head;
//         int nomor = 1;

//         while (current != NULL) {
//             cout << "[" << nomor << "]" << endl;
//             cout << "Nama: " << kapital(current->nama, true, true) << endl;
//             cout << "PIN: " << current->pin << endl;
//             cout << "Nomor Kartu: " << current->nomorKartu << endl;
//             cout << "Jumlah Saldo: Rp" << current->jumlahSaldo << endl << endl;

//             tampilkanRiwayatTransaksi(current);

//             current = current->next;
//             nomor += 1;
//         } cout << endl;
//     } else {
//         cout << "Belum ada nasabah yang terdaftar." << endl;
//     } system("pause");
// }

void cetakSemuaNasabah(NASABAH* head) {
    NASABAH* temp = head;

    if (temp == nullptr) {
        cout << "Tidak ada nasabah yang terdaftar." << endl;
        return;
    }

    cout << "Data Nasabah:" << endl;

    while (temp != nullptr) {
        cout << "Nama: " << temp->nama << endl;
        cout << "Nomor Kartu: " << temp->nomorKartu << endl;
        cout << "PIN: " << temp->pin << endl;
        cout << "Saldo: " << temp->jumlahSaldo << endl;
        cout << "---------------------" << endl;
        temp = temp->next;
    }
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

// void tambahTransaksi(NASABAH *nasabah, int nominal, string keterangan) {
//     if (nasabah != nullptr) {
//         Transaksi transaksiBaru;
//         transaksiBaru.jumlah = nominal;
//         transaksiBaru.keterangan = keterangan;

//         time_t now = time(0);
//         char* dt = ctime(&now);
//         dt[strlen(dt) - 1] = '\0';
//         transaksiBaru.waktu = string(dt);

//         nasabah->riwayatTransaksi.push_back(transaksiBaru);
//     }
// }

// void ubahSaldo(NASABAH* nasabah, int nominal, bool isTambah) {
//     if (nasabah != nullptr) {
//         if (isTambah) {
//             nasabah->jumlahSaldo += nominal;
//             tambahTransaksi(nasabah, nominal, "SETOR TUNAI");
//         } else {
//             nasabah->jumlahSaldo -= nominal;
//             tambahTransaksi(nasabah, nominal, "TRANSFER");
//         }
//     } else {
//         cout << "NODE Nasabah == NULL";
//     }
// }

int masuk(string nomorKartu, string pin) {
    NASABAH *current;
    current = head;

    // linear search
    while (current != NULL) {
        // three possible ouput used to represent loggedin, wrong pin, and not registered
        if (nomorKartu == current->nomorKartu && pin == current -> pin) {
            return 0;
        } 
        else if (nomorKartu == current->nomorKartu && pin != current->pin) {
            return 1;
        } 
        current = current->next;
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

bool daftar(string nama, string pin, int saldoAwal) {
    string nomorKartu = "000" + buatNomorRandom(3);
    
    // register new user if not registered yet (based on its nama)
    if (!isUseExist(nama, nomorKartu)) {
        tambahAkun(nama, pin, nomorKartu, saldoAwal);
        return false;
    } else {
        return true;
    }
}

void rekamTransaksi(NASABAH* nasabah, const string& keterangan, int jumlah) {
    Transaksi transaksi;
    transaksi.keterangan = keterangan;
    transaksi.jumlah = jumlah;
    transaksi.waktu = time(nullptr); // Waktu saat ini
    nasabah->riwayatTransaksi.push_back(transaksi);
}

void menuTransfer(NASABAH* head, NASABAH* nasabah) 
{
    printJudul();
    cout << "Menu Transfer\n\n";

    string nomorKartuTujuan;
    cout << "Masukkan Nomor Kartu Tujuan: ";
    cin >> nomorKartuTujuan;

    NASABAH* tujuan = cariNasabahTransfer(head, nomorKartuTujuan);
    if (tujuan == nullptr) 
    {
        cout << "Nomor Kartu tujuan tidak valid.\n";
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    int jumlahTransfer;
    cout << "Masukkan Jumlah Transfer: Rp. ";
    cin >> jumlahTransfer;

    if (jumlahTransfer <= 0) 
    {
        cout << "Jumlah transfer tidak valid.\n";
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    if (nasabah->jumlahSaldo < jumlahTransfer) 
    {
        cout << "Saldo Anda tidak mencukupi untuk melakukan transfer ini.\n";
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    nasabah->jumlahSaldo -= jumlahTransfer;
    tujuan->jumlahSaldo += jumlahTransfer;

    cout << "Transfer berhasil dilakukan.\n";
    cout << "Sisa saldo Anda: Rp. " << nasabah->jumlahSaldo << endl;
    this_thread::sleep_for(chrono::seconds(1));

    // Merekam transaksi pada pengirim dan penerima
    rekamTransaksi(nasabah, "Transfer keluar ke " + tujuan->nama, jumlahTransfer);
    rekamTransaksi(tujuan, "Transfer masuk dari " + nasabah->nama, jumlahTransfer);
}

void tampilkanRiwayatTransaksi(NASABAH* nasabah) 
{
    printJudul();
    cout << "Riwayat Transaksi\n\n";

    if (nasabah->riwayatTransaksi.empty()) {
        cout << "Tidak ada transaksi.\n";
    } else {
        for (const Transaksi& transaksi : nasabah->riwayatTransaksi) {
            cout << "Waktu: " << ctime(&transaksi.waktu); // Konversi waktu ke string
            cout << "Keterangan: " << transaksi.keterangan << endl;
            cout << "Jumlah: Rp. " << transaksi.jumlah << endl;
            cout << "---------------------" << endl;
        }
    }

    cout << "\n[1] Kembali ke Menu Utama\n";
    cout << "\n\n> ";
    int opsi;
    cin >> opsi;
}

void menuUtama(NASABAH* head, NASABAH* nasabah) {
    while (true) {
        printJudul();
        cout << "[1] Cek Saldo\n";
        cout << "[2] Riwayat Transaksi\n";
        cout << "[3] Profile\n";
        cout << "[4] Transfer\n";
        cout << "[5] Setor Tunai\n";
        cout << "[6] Keluar\n";

        string pilihan; cout << "\n> "; cin >> pilihan;

        if (pilihan == "1")
        {
            cout << "ini adalah menu cek saldo";
            break;
        }
        else if (pilihan == "2")
        {
            tampilkanRiwayatTransaksi(nasabah);
        }
        else if (pilihan == "3")
        {
            cout << "ini adalah menu Profile";
            break;
        }
        else if (pilihan == "4")
        {
            menuTransfer(head, nasabah);
        }
        else if (pilihan == "5")
        {
            cout << "ini adalah menu Setor Tunai";
            break;
        }
        else if (pilihan == "6")
        {
            cout << "ini adalah menu Logout";
            break;
        }
        else
        {
            cout << "Tolong input pilihan dengan benar\n";
        }
    } 
    this_thread::sleep_for(chrono::seconds(1));
}



int main() 
{
    // NASABAH* head = nullptr;

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

    NASABAH* head = nullptr;
    while (true) 
    {
        cetakSemuaNasabah(head);
        // NASABAH* head = NULL;
        programUtama:
            tampilkanHeader(selamatDatang, 2, "#=#=", 32);

            string opsi = menu(opsiMenuUtama, 4, false);

            if (opsi == "1") {
                goto menuMasuk;
            } else if (opsi == "2") {
                goto menuDaftar;
            } 
            // else if (opsi == "3") {
            //     goto menuDaftarNasabah;
            // } 
            else if (opsi == "4") {
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
                    } 
                    
                    verifyingMasuk: 
                    isLoggedin = masuk(kartuMasuk, pinMasuk);

                    if (isLoggedin == 0) {
                        // next step here
                        // good luck 👌
                        peringatan("Halo, " + kapital(namaMasuk, true, true) +  "!", false, false);
                        peringatan("Selamat datang di ATM Kantongku");
                        menuUtama(head, nasabah);
                        main();
                    } 
                    else if (isLoggedin == 1) {
                        limit -= 1;
                        if (limit == 0) {
                            peringatan("Batas percobaan PIN telah terlampaui.");
                            goto programUtama;
                        }

                        peringatan("PIN yang Anda masukkan salah!", false, false);
                        peringatan("Batas percobaan " + to_string(limit) + "x lagi.");
                        goto inputPinMasukLoop;
                    } 
                    else if (isLoggedin == 2) {
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
                            } 
                            
                        cout << endl; system("pause");

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

                // isRegistered = daftar(namaDaftar, pinDaftar);

                // if (isRegistered) {
                //     peringatan("Nasabah dengan nama ini sudah terdaftar!", false, false);
                //     peringatan("Menuju ke MENU MASUK...");
                //     goto menuMasuk;
                // } else {
                //     kartuDaftar = cariNasabahNama(head, namaDaftar)->nomorKartu;
                //     cout << "Nomor Kartu: " << kartuDaftar << endl;
                // }

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

                isRegistered = daftar(namaDaftar, pinDaftar, saldoAwalDaftar);

                if (isRegistered) {
                    peringatan("Nasabah dengan nama ini sudah terdaftar!", false, false);
                    peringatan("Menuju ke MENU MASUK...");
                    goto menuMasuk;
                } else {
                    kartuDaftar = cariNasabahNama(head, namaDaftar)->nomorKartu;
                    cout << "Nomor Kartu: " << kartuDaftar << endl;
                }

                peringatan("Selamat datang nasabah baru!");
                goto programUtama;

            // menuDaftarNasabah:
            //     tampilkanHeader(headerDaftar, 2, "#=#=", 32);
            //     NASABAH* head = nullptr;
            //     cetakSemuaNasabah(head);
            //     continue;

            menuKeluar:
                peringatan("Terima kasih telah menggunakan ATM Kantongku", false, false);
                peringatan("Sampai jumpa :D");
                break;
            
            menuTidakValid:
                peringatan("Input tidak valid!");
                continue;
    } return 0;
}
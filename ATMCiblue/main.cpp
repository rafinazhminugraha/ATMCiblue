#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <conio.h>
#include <string>
using namespace std;


void printJudul(string judul)
{
    cout << "\033[2J\033[1;1H";
    cout << "=====================\n";
    cout << "ATM Ciblue (" << judul << ")" << "\n";
    cout << "=====================\n\n";
}

string konvertTampilanPin() 
{
    string password;
    char huruf;
    while (true) 
    {
        huruf = _getch(); 
        if (huruf == '\r') 
        {
            break;
        }
        password.push_back(huruf); 
        cout << '*'; 
    }
    cout << endl;
    return password;
}

// hierarcial struct used to pack transaction data
struct Transaksi 
{
    string keterangan;
    int jumlah;
    time_t waktu;
};

// double linked list struct
struct NASABAH 
{
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

bool kosong() 
{
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

    if (kosong() || nama.compare(head->nama) < 0) 
    {
        nodeBaru -> next = head;
        nodeBaru -> prev = NULL;
        if (head != NULL)
            head -> prev = nodeBaru;
        head = nodeBaru;
    } 
    else 
    {
        NASABAH* temp = head;

        while (temp->next != NULL && nama.compare(temp->next->nama) >= 0) 
        {
            temp = temp->next;
        }
        if (temp -> next != NULL) 
        {
            nodeBaru -> next = temp -> next;
            nodeBaru -> prev = temp;
            temp -> next -> prev = nodeBaru;
            temp -> next = nodeBaru;
        } 
        else 
        {
            temp -> next = nodeBaru;
            nodeBaru -> prev = temp;
            nodeBaru -> next = NULL;
        }
    }
}

void hapusBaris(int baris) 
{
    if (baris > 0) {
        cout << "\x1b[2K";
        for (int i = 1; i < baris; i++) {
            cout << "\x1b[1A" << "\x1b[2K";
        } cout << "\r";
    }
}

string kapital(string kata, bool kapital, bool judul) 
{
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

int cekString(string str, bool isDigit, char spesial = '<') 
{
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

string buatNomorRandom(int panjang) 
{
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

void cetakSemuaNasabah(NASABAH* head) 
{
    NASABAH* temp = head;

    if (temp == nullptr) {
        cout << "Tidak ada nasabah yang terdaftar." << endl;
        return;
    }

    cout << "Data Nasabah:\n---------------------\n";

    while (temp != nullptr) {
        cout << "Nama: " << temp->nama << endl;
        cout << "Nomor Kartu: " << temp->nomorKartu << endl;
        cout << "PIN: " << temp->pin << endl;
        cout << "Saldo: " << temp->jumlahSaldo << endl;
        cout << "---------------------" << endl;
        temp = temp->next;
    }
}

void peringatan(string teks, bool jeda = true, bool bersihkan = true, bool back = false) 
{
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

string menu(string opsi[], int banyak, bool bersihkan) 
{
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

NASABAH* cariNasabahKartu(NASABAH *head, string nomorKartu) 
{
    NASABAH* current = head;

    while (current != nullptr) {
        if (nomorKartu == current->nomorKartu) {
            return current;
        } current = current->next;
    } return nullptr;
}

NASABAH* cariNasabahNama(NASABAH *head, string nama) 
{
    NASABAH* current = head;

    while (current != nullptr) {
        if (nama == current->nama) {
            return current;
        } current = current->next;
    } return nullptr;
}

int masuk(string nomorKartu, string pin) {
    NASABAH *current;
    current = head;

    // linear search
    while (current != NULL) 
    {
        if (nomorKartu == current->nomorKartu && pin == current -> pin) {
            return 0;
        } 
        else if (nomorKartu == current->nomorKartu && pin != current->pin) {
            return 1;
        } 
        current = current->next;
    } return 2;
}

bool isUseExist(string nama, string nomorKartu) 
{
    NASABAH *current;
    current = head;

    while (current != NULL) {
        if (nama == current->nama && nomorKartu == current->nomorKartu) {
            return true;
        } current = current->next;
    } return false;
}

bool daftar(string nama, string pin, int saldoAwal) 
{
    string nomorKartu = "000" + buatNomorRandom(3);
    
    // register new user if not registered yet (based on its nama)
    if (!isUseExist(nama, nomorKartu)) {
        tambahAkun(nama, pin, nomorKartu, saldoAwal);
        return false;
    } else {
        return true;
    }
}

void rekamTransaksi(NASABAH* nasabah, const string& keterangan, int jumlah) 
{
    Transaksi transaksi;
    transaksi.keterangan = keterangan;
    transaksi.jumlah = jumlah;
    transaksi.waktu = time(nullptr); // Waktu saat ini
    nasabah->riwayatTransaksi.push_back(transaksi);
}

void menuTransfer(NASABAH* head, NASABAH* nasabah) 
{
    while (true)
    {
        printJudul("Transfer");

        cout << "Input (<) untuk KEMBALI\n\n";
        string nomorKartuTujuan;
        cout << "Masukkan Nomor Kartu Tujuan: ";
        cin >> nomorKartuTujuan;

        if (nomorKartuTujuan == "<")
        {
            return;
        }
        
        NASABAH* tujuan = cariNasabahTransfer(head, nomorKartuTujuan);
        if (tujuan == nullptr) 
        {
            cout << "Nomor Kartu tujuan tidak valid.\n";
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }

        string jumlahTransfer;
        cout << "Masukkan Jumlah Transfer: Rp. ";
        cin >> jumlahTransfer;

        if (jumlahTransfer == "<")
        {
            return;
        }

        int jumlahTransferInt = stoi(jumlahTransfer);

        if (jumlahTransferInt <= 0) 
        {
            cout << "Jumlah transfer tidak valid.\n";
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }

        if (nasabah->jumlahSaldo < jumlahTransferInt) 
        {
            cout << "Saldo Anda tidak mencukupi untuk melakukan transfer ini.\n";
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }

        nasabah->jumlahSaldo -= jumlahTransferInt;
        tujuan->jumlahSaldo += jumlahTransferInt;

        cout << "Transfer berhasil dilakukan.\n";
        cout << "Sisa saldo Anda: Rp. " << nasabah->jumlahSaldo << endl;
        this_thread::sleep_for(chrono::seconds(1));

        // Merekam transaksi pada pengirim dan penerima
        rekamTransaksi(nasabah, "Transfer keluar ke " + tujuan->nama, jumlahTransferInt);
        rekamTransaksi(tujuan, "Transfer masuk dari " + nasabah->nama, jumlahTransferInt);
        return;
    }
}

void tampilkanRiwayatTransaksi(NASABAH* nasabah) 
{
    while (true)
    {
        printJudul("Riwayat Transaksi");
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
        
        string opsi; cout << "\n\nOpsi: "; cin >> opsi;

        if (opsi == "1")
        {
            break;
        }
        else
        {
            cout << "Inputan Invalid\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void cekSaldo(NASABAH* nasabah) {
    while (true) {
        printJudul("Cek Saldo");
        cout << "Sisa Saldo Anda: Rp." << nasabah->jumlahSaldo << endl;

        cout << "\n[1] Kembali ke Menu Utama";

        string opsi; cout << "\n\nOpsi: "; cin >> opsi;

        if (opsi == "1")
        {
            break;
        }
        else
        {
            cout << "Inputan Invalid\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void ubahNama(NASABAH* nasabah) 
{
    while (true) {
        printJudul("Profile");

        cout << "Input (<) untuk KEMBALI\n\n";
        string namaBaru;
        cout << "Masukkan nama baru: ";
        cin.ignore(); 
        getline(std::cin, namaBaru);

        if (namaBaru == "<") {
            return; 
        }

        nasabah->nama = namaBaru; 
        cout << "Nama berhasil diubah.\n";
        this_thread::sleep_for(std::chrono::seconds(1));
        break;
    }
}

void ubahPin(NASABAH* nasabah)
{
    while (true)
    {
        printJudul("Profile");

        cout << "Input (<) untuk KEMBALI\n\n";
        string pinBaru; cout << "Masukkan PIN baru: ";
        pinBaru = konvertTampilanPin();

        if (pinBaru == "<")
        {
            return;
        }
        
        nasabah->pin = pinBaru;
        cout << "PIN berhasil diubah.\n";
        this_thread::sleep_for(chrono::seconds(1));
        break;
    }
}

void menuProfile(NASABAH* nasabah) 
{
    bool isNamaAlpha; bool namaLimit; bool kartuLimit;
    while (true) 
    {   
        printJudul("Profile");
        cout << "Profile\n\n";

        cout << "Nama: " << nasabah->nama << endl;
        cout << "Nomor Kartu: " << nasabah->nomorKartu << endl;
        cout << "PIN: " << nasabah->pin << endl;

        cout << "\n[1] Edit Nama";
        cout << "\n[2] Edit PIN";
        cout << "\n[3] Kembali ke Menu Utama";
        cout << "\n\nOpsi: ";

        string opsi;
        cin >> opsi;

        if (opsi == "1")
        {   
            ubahNama(nasabah);
        }
        else if (opsi == "2")
        {   
            ubahPin(nasabah);
        }
        else if (opsi == "3")
        {
            return;
        }
        else
        {
            cout << "Input Invalid\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void menuSetortunai(NASABAH* head, NASABAH* nasabah) 
{
    while(true)
    {
        printJudul("Setor Tunai");
        cout << "Input (<) untuk KEMBALI\n\n";
        string jumlahSetorTunai;
        cout << "Masukkan Jumlah Setor Tunai: Rp. ";
        cin >> jumlahSetorTunai;

        if (jumlahSetorTunai == "<")
        {
            return;
        }

        int jumlahSetorTunaiInt = stoi(jumlahSetorTunai);

        if (jumlahSetorTunaiInt <= 0) 
        {
            cout << "Jumlah setor tunai tidak valid.\n";
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }

        nasabah->jumlahSaldo += jumlahSetorTunaiInt;

        string keterangan = "Setor Tunai";
        rekamTransaksi(nasabah, keterangan, jumlahSetorTunaiInt);

        cout << "Setor Tunai berhasil dilakukan.\n";
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }
}

void menuUtama(NASABAH* head, NASABAH* nasabah) {
    while (true) 
    {
        printJudul("Menu");
        cout << "[1] Cek Saldo\n";
        cout << "[2] Riwayat Transaksi\n";
        cout << "[3] Profile\n";
        cout << "[4] Transfer\n";
        cout << "[5] Setor Tunai\n";
        cout << "[6] Keluar\n";

        string pilihan; cout << "\nOpsi: "; cin >> pilihan;

        if (pilihan == "1")
        {
            cekSaldo(nasabah);
        }
        else if (pilihan == "2")
        {
            tampilkanRiwayatTransaksi(nasabah);
        }
        else if (pilihan == "3")
        {
            menuProfile(nasabah);
        }
        else if (pilihan == "4")
        {
            menuTransfer(head, nasabah);
        }
        else if (pilihan == "5")
        {
            menuSetortunai(head, nasabah);
        }
        else if (pilihan == "6")
        {
            system("cls");
            cout << "Berhasil Keluar\nEnter Untuk Melanjutkan...";
            system("pause");
            return;
        }
        else
        {
            cout << "Input Invalid\n";
        }
    } 
    this_thread::sleep_for(chrono::seconds(1));
}

int main() 
{
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
    string opsiMenuUtama[] = {"masuk", "daftar", "keluar"};


    while (true) 
    {
        programUtama:
            printJudul("Welcome");
            cetakSemuaNasabah(head);
            cout << "\n";
            string opsi = menu(opsiMenuUtama, 3, false);

            if (opsi == "1") {
                goto menuMasuk;
            } else if (opsi == "2") {
                goto menuDaftar;
            } else if (opsi == "3") {
                goto menuKeluar;
            } else {
                goto menuTidakValid;
            } 

            menuMasuk:
                while (true) {
                    printJudul("Masuk");
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
                                namaLimit = namaMasuk.length() >= 3;
                                
                                if (namaMasuk == "<") {
                                    goto menuMasuk;
                                } if (isNamaAlpha && namaLimit) {
                                    goto inputPinMasuk;
                                } if (!isNamaAlpha) {
                                    peringatan("Nama hanya terdiri dari huruf.", false, false);
                                } if (!namaLimit) {
                                    peringatan("Nama minimal terdiri dari 8 karakter.", false, false);
                                } cout << endl; system("pause");

                            printJudul("Masuk");
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

                            printJudul("Masuk");
                            peringatan("Input (<) untuk KEMBALI", false, false, true);
                            continue;
                        }

                    inputPinMasuk:
                        while (limit > 0) {
                            cout << "PIN: ";
                            pinMasuk = konvertTampilanPin();

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

                            printJudul("Masuk");
                            peringatan("Input (<) untuk KEMBALI", false, false, true);
                            if (opsi == "1") {
                                cout << "Nama: " << kapital(namaMasuk, true, true) << endl;
                            }
                            else if (opsi == "2") {
                                cout << "Nomor Kartu: " << kartuMasuk << endl;
                            }
                            continue;

                            inputPinMasukLoop:
                                printJudul("Masuk");
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

                    if (isLoggedin == 0) 
                    {
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
                printJudul("Daftar");
                peringatan("Input (<) untuk KEMBALI", false, false, true);

                inputNamaDaftar:
                    while (true) {
                        cout << "Nama: "; cin.ignore(); getline(cin, namaDaftar); 
                        namaDaftar = kapital(namaDaftar, false, false);

                        cekNamaDaftar:
                            isNamaAlpha = cekString(namaDaftar, false) == 0;
                            namaLimit = namaDaftar.length() >= 3;

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

                        printJudul("Daftar");
                        peringatan("Input (<) untuk KEMBALI", false, false, true);
                        cout << "Nama: "; getline(cin, namaDaftar); 
                        namaDaftar = kapital(namaDaftar, false, false);
                        goto cekNamaDaftar;
                    }

                inputPinDaftar:
                    while (true) {
                        cout << "PIN: ";
                        pinDaftar = konvertTampilanPin();

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

                        printJudul("Daftar");
                        peringatan("Input (<) untuk KEMBALI", false, false, true);
                        cout << "Nama: " << kapital(namaDaftar, true, true) << endl;
                        continue;
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

                        printJudul("Daftar");
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

            menuKeluar:
                peringatan("Terima kasih telah menggunakan ATM Kantongku", false, false);
                peringatan("Sampai jumpa :D");
                break;
            
            menuTidakValid:
                peringatan("Input tidak valid!");
                continue;
    } return 0;
}
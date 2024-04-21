#include <iostream>
using namespace std;

// hierarcial struct used to pack user data
struct DATA {
    string nama;
    string pin;
    string nomorKartu;
};

// double linked list struct
struct NODE {
    DATA user;
    NODE *prev;
    NODE *next;
};

NODE *head;
NODE *tail;

bool kosong() {
    if (head == NULL) {
        return true;
    } return false;
}

void tambahAwal(string nama, string pin, string nomorKartu) {
    NODE *nodeBaru;
    nodeBaru = new NODE;
    nodeBaru -> user.nama = nama;
    nodeBaru -> user.pin = pin;
    nodeBaru -> user.nomorKartu = nomorKartu;

    if (kosong()) {
        head = nodeBaru;
        head -> next = NULL;
    } else {
        nodeBaru -> next = head;
        nodeBaru -> prev = NULL;
        head = nodeBaru;
    }
}

void hapusAkhir() {
    NODE *hapus, *current;
    string nama, pin, nomorKartu;

    if (kosong()) {
        head = NULL;
    } else if (head -> next == NULL) {
        hapus = head;
        head = NULL; tail = NULL;
        delete hapus;
    } else {
        current = head;
        while (current -> next -> next != NULL) {
            current = current -> next;
        } delete current -> next;

        current -> next = NULL;
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
    NODE *current;
    current = head;

    string nomor = "";
    srand(time(0));
    
    for (int i = 0; i < panjang; i++) {
        nomor += to_string(rand() % 9);
    } while (current != NULL) {
        if (nomor == current -> user.nomorKartu) {
            buatNomorRandom(panjang);
        } current = current -> next;
    } return nomor;
}

void tampilkanList() {
    system("cls");

    if (!kosong()) {
        NODE *current;
        current = head;
        int nomor = 1;

        while (current != NULL) {
            cout << "List [" << nomor << "]" << endl;
            cout << "Nama	     : " << kapital(current -> user.nama, true, true) << endl;
            cout << "PIN	     : " << current -> user.pin << endl;
            cout << "Nomor Kartu : " << current -> user.nomorKartu << endl << endl;

            current = current -> next;
            nomor += 1;
        } cout << endl;
    } else {
        cout << "List masih kosong." << endl;
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

string getData(string nama, string pin, string dataUser) {
    NODE *current;
    current = head;

    // linear search
    while (current != NULL) {
        if (nama == current -> user.nama && pin == current -> user.pin) {
            if (dataUser == "nama") {
                return current -> user.nama;
            } else if (dataUser == "nomorKartu") {
                return current -> user.nomorKartu;
            } else if (dataUser == "pin") {
                return current -> user.pin;
            }
        }
    } return "invalid";
}

int masuk(string nama, string nomorKartu, string pin) {
    NODE *current;
    current = head;

    // linear search
    while (current != NULL) {
        // three possible ouput used to represent loggedin, wrong pin, and not registered
        if ((nama == current -> user.nama || nomorKartu == current -> user.nomorKartu) && pin == current -> user.pin) {
            return 0;
        } else if ((nama == current -> user.nama || nomorKartu == current -> user.nomorKartu) && pin != current -> user.pin) {
            return 1;
        } current = current -> next;
    } return 2;
}

bool daftar(string nama, string pin) {
    string nomorKartu = "000" + buatNomorRandom(3);
    
    // register new user if not registered yet (based on its nama)
    if (masuk(nama, pin, nomorKartu) == 2) {
        tambahAwal(nama, pin, nomorKartu);
        return false;
    } else {
        return true;
    }
}

int main() {
    string namaMasuk, pinMasuk, kartuMasuk;
    string namaDaftar, pinDaftar, kartuDaftar;
    int limit = 3;
    int isLoggedin;
    bool isRegistered;
    bool isNamaAlpha; bool namaLimit; bool kartuLimit;
    bool isPinDigit; bool pinLimit; bool isKartuDigit;

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
                goto menuTampilan;
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
                            cout << "Nama	     : "; cin.ignore(); getline(cin, namaMasuk);
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
                            cout << "Nama	     : "; getline(cin, namaDaftar); 
                            namaMasuk = kapital(namaMasuk, false, false);
                            goto cekNamaMasuk;
                        }

                    inputNomorMasuk:
                        while (true) {
                            cout << "Nomor Kartu : "; cin >> kartuMasuk;

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
                            cout << "PIN	     : "; cin >> pinMasuk;

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
                            cout << "Nama	     : " << kapital(namaMasuk, true, true) << endl;
                            cout << "Nomor Kartu : " << kartuMasuk << endl;
                            continue;

                            inputPinMasukLoop:
                                tampilkanHeader(headerMasuk, 2, "#=#=", 32);
                                peringatan("Input (<) untuk KEMBALI", false, false, true);
                                cout << "Nama        : " << kapital(namaMasuk, true, true) << endl;
                                cout << "Nomor Kartu : " << kartuMasuk << endl;
                                cout << "PIN         : "; cin >> pinMasuk;
                                goto cekPinMasuk;

                        }
                    
                    isLoggedin = masuk(namaMasuk, kartuMasuk, pinMasuk);

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
                    } else {
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
                        cout << "Nama	     : "; cin.ignore(); getline(cin, namaDaftar); 
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
                        cout << "Nama	     : "; getline(cin, namaDaftar); 
                        namaDaftar = kapital(namaDaftar, false, false);
                        goto cekNamaDaftar;
                    }

                inputPinDaftar:
                    while (true) {
                        cout << "PIN	     : "; cin >> pinDaftar;

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
                        cout << "Nama   : " << kapital(namaDaftar, true, true) << endl;
                        continue;
                    }

                isRegistered = daftar(namaDaftar, pinDaftar);

                if (isRegistered) {
                    peringatan("Nasabah dengan nama ini sudah terdaftar!", false, false);
                    peringatan("Menuju ke MENU MASUK...");
                    continue;
                } else {
                    kartuDaftar = getData(namaDaftar, pinDaftar, "nomorKartu");
                    cout << "Nomor Kartu : " << kartuDaftar << endl;
                    peringatan("Selamat datang nasabah baru!");
                    goto menuMasuk;
                }

            menuTampilan:
                tampilkanHeader(headerDaftar, 2, "#=#=", 32);
                tampilkanList();
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
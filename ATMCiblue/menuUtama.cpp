// #include <iostream>
// #include <chrono>
// #include <thread>
// #include "main.cpp"
// using namespace std;

// struct NASABAH;

// void printJudul() {
//     cout << "\033[2J\033[1;1H";
//     cout << "=============\n";
//     cout << "     ATM     \n";
//     cout << "=============\n";
// }

// void menuUtama(NASABAH* head, NASABAH* nasabah) {
//     while (true) {
//         printJudul();
//         cout << "[1] Cek Saldo\n";
//         cout << "[2] Riwayat Transaksi\n";
//         cout << "[3] Profile\n";
//         cout << "[4] Transfer\n";
//         cout << "[5] Setor Tunai\n";
//         cout << "[6] Keluar\n";

//         string pilihan; cout << "\n> "; cin >> pilihan;

//         if (pilihan == "1")
//         {
//             cout << "ini adalah menu cek saldo";
//             break;
//         }
//         else if (pilihan == "2")
//         {
//             cout << "ini adalah menu Riwayat Transaksi";
//             break;
//         }
//         else if (pilihan == "3")
//         {
//             cout << "ini adalah menu Profile";
//             break;
//         }
//         else if (pilihan == "4")
//         {
//             menuTransfer(head, nasabah);
//         }
//         else if (pilihan == "5")
//         {
//             cout << "ini adalah menu Setor Tunai";
//             break;
//         }
//         else if (pilihan == "6")
//         {
//             cout << "ini adalah menu Logout";
//             break;
//         }
//         else
//         {
//             cout << "Tolong input pilihan dengan benar\n";
//         }
//     } 
//     this_thread::sleep_for(chrono::seconds(1));
// }
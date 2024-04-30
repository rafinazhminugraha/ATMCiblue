#include <iostream>
#include <string>
#include <conio.h> // hanya untuk Windows

std::string getPassword() {
    std::string password;
    char ch;
    while (true) {
        ch = _getch(); // Untuk Windows, mengambil karakter tanpa menampilkannya
        if (ch == '\r') // jika Enter ditekan
            break;
        password.push_back(ch); // Tambahkan karakter ke password
        std::cout << '*'; // Tampilkan bintang sebagai ganti karakter
    }
    std::cout << std::endl;
    return password;
}

int main() {
    std::cout << "Masukkan password: ";
    std::string password = getPassword();
    std::cout << "Password yang dimasukkan: " << password << std::endl;

    return 0;
}

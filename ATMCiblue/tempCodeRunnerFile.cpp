#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstring>

std::string getPassword() {
    std::string password;
    struct termios oldt, newt;

    // Dapatkan pengaturan terminal saat ini
    tcgetattr(STDIN_FILENO, &oldt);

    // Salin pengaturan lama ke yang baru
    newt = oldt;

    // Non-kanonikal mode: karakter tidak disimpan dalam buffer hingga Enter ditekan
    newt.c_lflag &= ~(ICANON);

    // Tidak menampilkan karakter yang dimasukkan ke terminal
    newt.c_lflag &= ~(ECHO);

    // Terapkan pengaturan baru
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Baca password karakter demi karakter
    char ch;
    while (true) {
        std::cin.get(ch);
        if (ch == '\n') // Jika pengguna menekan Enter
            break;
        password.push_back(ch); // Tambahkan karakter ke password
    }

    // Kembalikan pengaturan terminal ke kondisi semula
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return password;
}

int main() {
    std::cout << "Masukkan password: ";
    std::string password = getPassword();
    std::cout << "\nPassword yang dimasukkan: " << password << std::endl;

    return 0;
}

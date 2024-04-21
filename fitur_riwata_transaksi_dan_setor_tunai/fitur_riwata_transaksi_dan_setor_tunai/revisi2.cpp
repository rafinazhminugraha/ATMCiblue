#include <iostream>
#include <string>

using namespace std;

struct transaksi{
    string type;
    int amount;
    transaksi* next;
};

struct akun{
    string username;
    string password;
    int saldo;
    transaksi* transaksiHistory;
    akun* next;
};

akun* currentAkun = NULL;

//register akun
void resgisterAkun(){
    cout << "Masukan username: ";cin >> currentAkun ->username;
    cout << "Masukan password: ";cin >> currentAkun -> password;
    currentAkun -> saldo = 0;
    currentAkun -> transaksiHistory = NULL;
    cout << "Akun berhasil di daftarkan"<<endl;
}


bool login(){
    string username, password;
    cout<<"Masukan username: "; cin >> username;
    cout<<"Masukan Password: "; cin>> password;
    if (username == currentAkun->username && password == currentAkun ->password){
        cout<<"Login berhasil"<< endl;
        return true;
    }else{
        cout << "Login Gagal" << endl;
        return false;
    }
}

void deposit(){
    int amount;
    cout << "Masukan jumlah deposit: "; cin >> amount;
    currentAkun -> saldo += amount;
    transaksi* newTransaksi = new transaksi;
    newTransaksi -> type = "Deposit";
    newTransaksi->amount = amount;
    newTransaksi->next=NULL;
    if(currentAkun->transaksiHistory==NULL){
        currentAkun->transaksiHistory=newTransaksi;
    }else{
        transaksi* current = currentAkun->transaksiHistory;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newTransaksi;
    }
    cout << "Deposit Berhasil!"<<endl;
}

void Riwayat(){
    transaksi* current = currentAkun -> transaksiHistory;
    cout << "Transaksi Histori: "<<endl;
    while(current != NULL){
        cout << current->type<<" "<<current->amount<<endl;
        current = current->next;
    }
}

//gerbang utama
int main(){
    akun account;
    currentAkun = &account;
    int pilihan;

    while(true){
        cout <<"1. Register\n2. Login\n3. Deposit\n4. View Transaction History\n5. Exit\nEnter choice: ";cin >>pilihan;
        switch(pilihan){
            case 1:
                resgisterAkun();
                break;
            case 2:
                if (currentAkun->username.empty())
                    cout << "Tolong daftar duli!!"<<endl;
                else
                    login();
                break;
            case 3:
                if (currentAkun->username.empty())
                    cout << "Tolong daftar dulu!"<< endl;
                else
                    deposit();
                break;
            case 4:
                if (currentAkun->username.empty())
                    cout<<"Tolong daftar duli!"<<endl;
                else
                    Riwayat();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}
// Main file for the backend logic: backend/main.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// Maximum number of students
const int MAX_MAHASISWA = 100;

struct Mahasiswa {
    string nama;
    double saldo;
};

// Global array and counter for storing mahasiswa data
Mahasiswa mahasiswaList[MAX_MAHASISWA];
int mahasiswaCount = 0;

// Function to load data from file
void loadData() {
    ifstream file("data.txt");
    if (file.is_open()) {
        mahasiswaCount = 0;
        while (file >> mahasiswaList[mahasiswaCount].nama >> mahasiswaList[mahasiswaCount].saldo) {
            mahasiswaCount++;
            if (mahasiswaCount >= MAX_MAHASISWA) break;
        }
        file.close();
    }
}

// Function to save data to file
void saveData() {
    ofstream file("data.txt");
    if (file.is_open()) {
        for (int i = 0; i < mahasiswaCount; i++) {
            file << mahasiswaList[i].nama << " " << mahasiswaList[i].saldo << endl;
        }
        file.close();
    }
}

// Function to add a new mahasiswa
void addMahasiswa(const string &nama, double saldoAwal) {
    if (mahasiswaCount < MAX_MAHASISWA) {
        mahasiswaList[mahasiswaCount].nama = nama;
        mahasiswaList[mahasiswaCount].saldo = saldoAwal;
        mahasiswaCount++;
        saveData();
    } else {
        cout << "Data mahasiswa penuh!" << endl;
    }
}

// Function to add saldo
bool addSaldo(const string &nama, double amount) {
    for (int i = 0; i < mahasiswaCount; i++) {
        if (mahasiswaList[i].nama == nama) {
            mahasiswaList[i].saldo += amount;
            saveData();
            return true;
        }
    }
    return false;
}

// Function to withdraw saldo
bool withdrawSaldo(const string &nama, double amount) {
    for (int i = 0; i < mahasiswaCount; i++) {
        if (mahasiswaList[i].nama == nama && mahasiswaList[i].saldo >= amount) {
            mahasiswaList[i].saldo -= amount;
            saveData();
            return true;
        }
    }
    return false;
}

// Function to display all mahasiswa data
void displayAllMahasiswa() {
    for (int i = 0; i < mahasiswaCount; i++) {
        cout << "Nama: " << mahasiswaList[i].nama << ", Saldo: " << mahasiswaList[i].saldo << endl;
    }
}

// Function to get total saldo of all mahasiswa
double getTotalSaldo() {
    double total = 0;
    for (int i = 0; i < mahasiswaCount; i++) {
        total += mahasiswaList[i].saldo;
    }
    return total;
}

// Function to withdraw all saldo
void withdrawAll() {
    for (int i = 0; i < mahasiswaCount; i++) {
        mahasiswaList[i].saldo = 0;
    }
    saveData();
}

int main() {
    loadData();
    int choice;

    do {
        cout << "\n=== Aplikasi Uang Kas Mahasiswa ===" << endl;
        cout << "1. Tampilkan Data Mahasiswa" << endl;
        cout << "2. Tambah Mahasiswa" << endl;
        cout << "3. Tambah Saldo Mahasiswa" << endl;
        cout << "4. Tarik Saldo Mahasiswa" << endl;
        cout << "5. Tampilkan Total Saldo" << endl;
        cout << "6. Tarik Semua Saldo" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 1) {
            displayAllMahasiswa();
        } else if (choice == 2) {
            string nama;
            double saldoAwal;
            cout << "Masukkan nama mahasiswa: ";
            cin >> nama;
            cout << "Masukkan saldo awal: ";
            cin >> saldoAwal;
            addMahasiswa(nama, saldoAwal);
        } else if (choice == 3) {
            string nama;
            double amount;
            cout << "Masukkan nama mahasiswa: ";
            cin >> nama;
            cout << "Masukkan jumlah saldo yang ditambahkan: ";
            cin >> amount;
            if (!addSaldo(nama, amount)) {
                cout << "Mahasiswa tidak ditemukan." << endl;
            }
        } else if (choice == 4) {
            string nama;
            double amount;
            cout << "Masukkan nama mahasiswa: ";
            cin >> nama;
            cout << "Masukkan jumlah saldo yang ditarik: ";
            cin >> amount;
            if (!withdrawSaldo(nama, amount)) {
                cout << "Saldo tidak mencukupi atau mahasiswa tidak ditemukan." << endl;
            }
        } else if (choice == 5) {
            cout << "Total saldo semua mahasiswa: " << getTotalSaldo() << endl;
        } else if (choice == 6) {
            withdrawAll();
            cout << "Semua saldo telah ditarik." << endl;
        }
    } while (choice != 0);

    cout << "Terima kasih telah menggunakan aplikasi ini." << endl;
    return 0;
}

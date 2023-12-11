#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

struct Motor {
    string merk;
    string tipe;
    string jenis;
    float hargaSewa;
    bool sedangDisewakan;
};

void displayMotorList(Motor arr[], int n) {
    cout << "\nDaftar Motor yang Tersedia:" << endl;
    for (int i = 0; i < n; ++i) {
        if (!arr[i].sedangDisewakan) {
            cout << "\nMotor " << i + 1 << ":" << endl;
            cout << "Merk: " << arr[i].merk << endl;
            cout << "Tipe: " << arr[i].tipe << endl;
            cout << "Jenis: " << arr[i].jenis << endl;
            cout << "Harga sewa per hari: " << arr[i].hargaSewa << endl;
        }
    }
}

vector<int> searchMotor(Motor arr[], int n, string keyword) {
    vector<int> hasilPencarian;

    for (int i = 0; i < n; ++i) {
        if (arr[i].merk == keyword || arr[i].tipe == keyword) {
            hasilPencarian.push_back(i);
        }
    }

    return hasilPencarian;
}

void bubbleSort(Motor arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].hargaSewa > arr[j + 1].hargaSewa) {
                Motor temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    const int jumlahMotor = 6;
    Motor daftarMotor[jumlahMotor] = {
        {"Honda", "Beat", "Matic", 50.0, true},
        {"Yamaha", "FZ25", "Matic", 70.0, false},
        {"Honda", "CBR", "Gigi", 100.0, true},
        {"Honda", "Supra", "Gigi", 90.0, false},
        {"Honda", "Vario", "Matic", 60.0, true},
        {"Yamaha", "XMAX", "Matic", 80.0, false},
    };

    Motor *ptrMotor = daftarMotor;

    bubbleSort(daftarMotor, jumlahMotor);

    char lanjutSewa = 'y';

    while (lanjutSewa == 'y' || lanjutSewa == 'Y') {
        displayMotorList(ptrMotor, jumlahMotor);

        string namaPemesan, tanggalPemesanan, alamatPemesan;

        cout << "\nMasukkan detail pemesanan:" << endl;
        cout << "Nama Pemesan: ";
        cin >> namaPemesan;
        cout << "Tanggal Pemesanan: ";
        cin >> tanggalPemesanan;
        cout << "Alamat Pemesan: ";
        cin.ignore();
        getline(cin, alamatPemesan);

        string keyword;
        cout << "\nMasukkan merk or tipe motor yang ingin Anda sewa: ";
        cin >> keyword;

        vector<int> hasilPencarian = searchMotor(ptrMotor, jumlahMotor, keyword);
        if (!hasilPencarian.empty()) {
            cout << "\nMotor " << keyword << " yang tersedia:" << endl;
            for (int i = 0; i < hasilPencarian.size(); ++i) {
                int index = hasilPencarian[i];
                if (!(ptrMotor + index)->sedangDisewakan) {
                    cout << i + 1 << ". " << daftarMotor[index].tipe << endl;
                }
            }

            int pilihanMotor;
            cout << "\nPilih motor " << keyword << " yang ingin Anda sewa (1-" << hasilPencarian.size() << "): ";
            cin >> pilihanMotor;

            int indeksMotor = hasilPencarian[pilihanMotor - 1];
            int jumlahHari;
            cout << "Masukkan jumlah hari sewa: ";
            cin >> jumlahHari;

            if (jumlahHari > 1) {
                float totalHarga = (ptrMotor + indeksMotor)->hargaSewa * jumlahHari;
                cout << "\nAnda telah menyewa motor " << (ptrMotor + indeksMotor)->merk << " " << (ptrMotor + indeksMotor)->tipe << " selama " << jumlahHari << " hari." << endl;
                cout << "Total harga yang harus dibayar: " << totalHarga << " IDR" << endl;
            } else {
                cout <<"Anda salah menginputkan jumlah hari"<<endl;
            }

            stack<Motor> motorStack;
            queue<Motor> motorQueue;

            for (int i = 0; i < jumlahMotor; ++i) {
                if ((ptrMotor + i)->sedangDisewakan) {
                    motorStack.push(*(ptrMotor + i));
                } else {
                    motorQueue.push(*(ptrMotor + i));
                }
            }

            cout << "\nMotor yang tersedia (Queue) sebelum pemesanan:" << endl;
            while (!motorQueue.empty()) {
                Motor motorQueueFront = motorQueue.front();
                cout << "Merk: " << motorQueueFront.merk << ", Tipe: " << motorQueueFront.tipe << endl;
                motorQueue.pop();
            }

            cout << "\nMotor yang sedang disewakan (Stack) sebelum pemesanan:" << endl;
            while (!motorStack.empty()) {
                Motor motorStackTop = motorStack.top();
                cout << "Merk: " << motorStackTop.merk << ", Tipe: " << motorStackTop.tipe << endl;
                motorStack.pop();
            }

            cout << "\nIngin memesan sewa motor lagi? (y/n): ";
            cin >> lanjutSewa;

            if (lanjutSewa == 'y' || lanjutSewa == 'Y') {
                if (hasilPencarian.size() > 0) {
                    int indexSewa = hasilPencarian[pilihanMotor - 1];
                    (ptrMotor + indexSewa)->sedangDisewakan = true;
                }
            } else {
                cout << "\nTerima kasih telah menggunakan layanan kami." << endl;
                break;
            }
        } else {
            cout << "Motor tidak ditemukan." << endl;
            break;
        }
    }
    return 0;
}

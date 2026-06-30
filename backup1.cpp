#include <iostream>
#include <string>

using namespace std;

struct Barang {
    string namaBarang;
    int codeBarang;
    int jumlahBarang;
};

void tambahBarang(Barang &barang)
{
    cin.ignore();

    cout << "Nama Barang : ";
    getline(cin, barang.namaBarang);
    cout << "Code Barang : ";
    cin >> barang.codeBarang;
    cout << "Jumlah Barang : ";
    cin >> barang.jumlahBarang;
}

void tampilBarang(Barang &barang) {
    for (int i = 0;) {
    // cout << "Nama barang : " << barang.namaBarang << endl;
    // cout << "Code barang : " << barang.codeBarang << endl;
    // cout << "Jumlah barang : " << barang.jumlahBarang << endl;
}

int main() {
    int pilihan;
    Barang barang;

    do {
        cout << "\n=== Menu Gudang ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Hapus Barang\n";
        cout << "4. Keluar\n";
        cout << "Masukkan Pilihan (1-4): ";
        cin >> pilihan;
        

        switch (pilihan) {
            case 1:
                tambahBarang(barang);
                break;
            case 2:
                tampilBarang(barang);
                break;
            case 3:
                // Hapus barang
                break;
            case 4:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 4);
}
#include <iostream>
#include <string>

using namespace std;

struct Barang
{
    string namaBarang;
    int codeBarang;
    int jumlahBarang;
};

void tambahBarang(Barang daftarBarang[], int &totalBarang)
{
    cin.ignore();
    cout << "Nama Barang : ";
    getline(cin, daftarBarang[totalBarang].namaBarang);
    cout << "Code Barang : ";
    cin >> daftarBarang[totalBarang].codeBarang;
    cout << "Jumlah Barang : ";
    cin >> daftarBarang[totalBarang].jumlahBarang;

    totalBarang++;
    cout << "Barang berhasil ditambahkan.\n";
}

void tampilBarang(Barang daftarBarang[], int totalBarang)
{
    if (totalBarang == 0)
    {
        cout << "Gudang masih kosong!\n";
        return;
    }
    cout << "\n=== Daftar Barang di Gudang ===\n";
    for (int i = 0; i < totalBarang; i++)
    {
        cout << i + 1 << ". Nama barang   : " << daftarBarang[i].namaBarang << endl;
        cout << "   Code barang   : " << daftarBarang[i].codeBarang << endl;
        cout << "   Jumlah barang : " << daftarBarang[i].jumlahBarang << endl;
        cout << "---------------------------\n";
    }
}

int main()
{
    int pilihan;
    Barang daftarBarang[100];
    int totalBarang = 0;

    do
    {
        cout << "\n=== Menu Gudang ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Hapus Barang (Belum Implementasi)\n";
        cout << "4. Keluar\n";
        cout << "Masukkan Pilihan (1-4): ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            if (totalBarang < 100) {
                tambahBarang(daftarBarang, totalBarang);
            } else {
                cout << "Gudang sudah penuh!\n";
            }
            break;
        case 2:
            tampilBarang(daftarBarang, totalBarang);
            break;
        case 3:
            cout << "Fitur hapus barang masih dalam pengembangan.\n";
            break;
        case 4:
            cout << "Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
        }
    } while (pilihan != 4);

    return 0;
}
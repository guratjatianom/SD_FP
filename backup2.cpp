#include <iostream>
#include <string>

using namespace std;

struct Barang {
    string namaBarang;
    int codeBarang;
    int jumlahBarang;
    Barang *next;
};

// PERBAIKAN 1: Menggunakan '&' (reference) agar nilai variabel 'tambah' di main() ikut berubah
void menuTambahBarang(int &tambah) {
    cout << "\n=== Menu Tambah Barang ===\n";
    cout << "1. Depan.\n";
    cout << "2. Tengah.\n";
    cout << "3. Belakang.\n";
    cout << "Masukan Pilihan : ";
    cin >> tambah;
}

Barang *head = NULL;

void tambahDepan(string namaBarang, int codeBarang, int jumlahBarang) {
    Barang *baru = new Barang;
    baru->namaBarang = namaBarang;
    baru->codeBarang = codeBarang;
    baru->jumlahBarang = jumlahBarang;

    baru->next = head;
    head = baru;

    cout << "Data berhasil ditambahkan di depan.\n";
}

// Parameter di fungsi tampil dihapus karena data diambil langsung dari global 'head'
void tampil() {
    if (head == NULL) {
         cout << "Linked List kosong.\n";
         return;
    }

    Barang *temp = head;
    cout << "\n=== Data Gudang Logistik ===\n";

    while (temp != NULL) {
        cout << "Nama Barang   : " << temp->namaBarang << endl;
        cout << "Code Barang   : " << temp->codeBarang << endl;
        cout << "Jumlah Barang : " << temp->jumlahBarang << "\n-------------\n";
        temp = temp->next;
    }
}

int main() {
    int pilihan, tambah;
    string namaBarang;
    int codeBarang;
    int jumlahBarang;

    do { 
        cout << "\n=== Menu Gudang ===\n";
        cout << "1. Masukan tambah barang.\n";
        cout << "2. Tampilkan barang.\n";
        cout << "3. Keluar.\n"; // Diubah ke 3 agar program tidak langsung keluar saat pilih tampilkan barang
        cout << "Masukan Pilihan (1-3) : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
        {
            menuTambahBarang(tambah);

            // PERBAIKAN 2: Membersihkan sisa 'Enter' dari cin >> tambah sebelumnya
            cin.ignore(); 

            cout << "\n=== Masukan Data Barang ===\n";
            cout << "Nama Barang   : ";
            getline(cin, namaBarang); // Sekarang bisa menggunakan spasi tanpa terlewati
            
            cout << "Code Barang   : ";
            cin >> codeBarang;
            
            cout << "Jumlah Barang : ";
            cin >> jumlahBarang;

            // PERBAIKAN 3: Memanggil fungsi sesuai pilihan sub-menu (sementara baru dibuat untuk Depan)
            if (tambah == 1) {
                tambahDepan(namaBarang, codeBarang, jumlahBarang);
            } else {
                cout << "Fitur tengah/belakang belum diimplementasikan.\n";
            }
            break;
        }
        case 2:
            tampil(); // Memanggil fungsi tampil tanpa argumen data mentah
            break;
        case 3:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
        }

    } while (pilihan != 3);

    return 0;
}
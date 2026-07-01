/**
 * PROJECT: SISTEM MANAJEMEN GUDANG LOGISTIK
 * KONSEP STRUKTUR DATA:
 * 1. Array (Penyimpanan Utama)
 * 2. Struct (Penyimpanan Data Majemuk)
 * 3. Searching (Pencarian Berdasarkan Kode)
 * 4. Sorting (Pengurutan Alphabetis)
 * 5. Pointer (Pass-By-Pointer untuk update total data)
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// KONSEP 2: Struct
// Menyimpan informasi dasar barang dalam satu tipe data majemuk
struct Barang
{
    string namaBarang;
    int codeBarang;
};

// KONSEP 3: Searching (Helper)
// Mencari indeks berdasarkan code
int cariIndeksBerdasarkanCode(Barang daftarBarang[], int totalBarang, int code)
{
    for (int i = 0; i < totalBarang; i++)
    {
        if (daftarBarang[i].codeBarang == code)
        {
            return i;
        }
    }
    return -1;
}

// Untuk mengecek keunikan kode agar tidak ada yang duplikat
bool cekCodeExist(Barang daftarBarang[], int totalBarang, int code)
{
    return cariIndeksBerdasarkanCode(daftarBarang, totalBarang, code) != -1;
}

// Menghitung total stok secara keseluruhan
int hitungTotalStok(int stokBarang[], int totalBarang)
{
    int total = 0;
    for (int i = 0; i < totalBarang; i++)
    {
        total += stokBarang[i];
    }
    return total;
}

// Mencari indeks berdasarkan nama (untuk merge stok)
int cariIndeksBerdasarkanNama(Barang daftarBarang[], int totalBarang, string nama)
{
    for (int i = 0; i < totalBarang; i++)
    {
        if (daftarBarang[i].namaBarang == nama)
        {
            return i;
        }
    }
    return -1;
}

// FUNGSI PERSISTENSI: Simpan data ke file txt
void simpanKeFile(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    ofstream file("gudang.txt");
    if (file.is_open())
    {
        file << totalBarang << endl;
        for (int i = 0; i < totalBarang; i++)
        {
            file << daftarBarang[i].namaBarang << endl;
            file << daftarBarang[i].codeBarang << endl;
            file << stokBarang[i] << endl;
        }
        file.close();
    }
}

// FUNGSI PERSISTENSI: Muat data dari file txt
void muatDariFile(Barang daftarBarang[], int stokBarang[], int *totalBarang)
{
    ifstream file("gudang.txt");
    if (file.is_open())
    {
        if (!(file >> *totalBarang)) return;
        file.ignore(); // Membersihkan buffer newline
        for (int i = 0; i < *totalBarang && i < 1000; i++)
        {
            getline(file, daftarBarang[i].namaBarang);
            file >> daftarBarang[i].codeBarang;
            file >> stokBarang[i];
            file.ignore(); // Membersihkan buffer newline
        }
        file.close();
    }
}

/**
 * OPERASI: BARANG MASUK (Pendaftaran Item Baru)
 * Barang baru akan dicatat pada posisi terakhir dalam daftar stok.
 * KONSEP 5: Pointer (int *totalBarang)
 */
void tambahBarang(Barang daftarBarang[], int stokBarang[], int *totalBarang)
{
    int stokSekarang = hitungTotalStok(stokBarang, *totalBarang);
    
    if (stokSekarang >= 1000) {
        cout << " [!] Gagal: Kapasitas gudang sudah mencapai batas (Maks 1000 unit).\n";
        return;
    }

    cout << "\n===============================================\n";
    cout << "        PROSES: PENERIMAAN BARANG BARU         \n";
    cout << "===============================================\n";
    cout << " Total Kapasitas : " << stokSekarang << " / 1000 Unit\n";
    cout << " Jenis Barang    : " << *totalBarang << " Barang Terdaftar\n";
    cout << "-----------------------------------------------\n";

    string nama;
    int jumlah;

    cout << "Nama Barang (Ketik 'q' untuk kembali): ";
    getline(cin, nama);

    if (nama == "q" || nama == "Q") {
        return;
    }

    // Cek duplikasi nama untuk merge stok
    int indexLama = cariIndeksBerdasarkanNama(daftarBarang, *totalBarang, nama);
    if (indexLama != -1) {
        cout << "Barang sudah ada. Menambah stok ketersediaan...\n";
        cout << "Masukkan jumlah tambahan : ";
        cin >> jumlah;

        if (stokSekarang + jumlah > 1000) {
            cout << "Gagal! Melebihi kapasitas total gudang.\n";
            return;
        }

        stokBarang[indexLama] += jumlah;
        cout << "Stok berhasil diperbarui.\n";
        return;
    }
    
    // Generate Code Unik (Otomatis)
    int generatedCode;
    do {
        generatedCode = rand() % 9000 + 1000;
    } while (cekCodeExist(daftarBarang, *totalBarang, generatedCode));

    cout << "Code Barang (Generated) : " << generatedCode << endl;
    cout << "Jumlah Barang : ";
    cin >> jumlah;

    if (stokSekarang + jumlah > 1000) {
        cout << "Gagal! Kapasitas gudang tidak mencukupi.\n";
        return;
    }

    // Masukkan data ke REAR antrian
    daftarBarang[*totalBarang].namaBarang = nama;
    daftarBarang[*totalBarang].codeBarang = generatedCode;
    stokBarang[*totalBarang] = jumlah;

    (*totalBarang)++;
    cout << " [v] Berhasil: Barang telah terdaftar di gudang.\n";
    simpanKeFile(daftarBarang, stokBarang, *totalBarang); // Simpan perubahan
}

// Menampilkan seluruh data dalam antrian
void tampilBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang == 0)
    {
        cout << " [!] Peringatan: Stok gudang sedang kosong!\n";
        return;
    }
    cout << "\n===============================================\n";
    cout << "           DAFTAR STOK BARANG GUDANG           \n";
    cout << "===============================================\n";
    for (int i = 0; i < totalBarang; i++)
    {
        cout << " [" << i + 1 << "] Nama : " << daftarBarang[i].namaBarang << endl;
        cout << "     Code : " << daftarBarang[i].codeBarang;
        cout << " | Stok : " << stokBarang[i] << endl;
        cout << "-----------------------------------------------\n";
    }
}

// KONSEP 3: Searching (Cari Barang)
void cariBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang == 0)
    {
        cout << " [!] Peringatan: Tidak dapat mencari, stok gudang sedang kosong!\n";
        return;
    }

    cout << "\n===============================================\n";
    cout << "          PENCARIAN DATA BARANG                \n";
    cout << "===============================================\n";
    string input;
    cout << " Masukkan Code Barang (Ketik 'q' untuk batal): ";
    cin >> input;

    if (input == "q" || input == "Q") {
        cout << " [!] Pencarian dibatalkan.\n";
        return;
    }

    int code = atoi(input.c_str());
    if (code == 0 && input != "0") {
        cout << " [!] Error: Kode harus berupa angka.\n";
        return;
    }

    int index = cariIndeksBerdasarkanCode(daftarBarang, totalBarang, code);

    if (index != -1)
    {
        cout << "\n [v] Barang Berhasil Ditemukan:\n";
        cout << " > Nama Item : " << daftarBarang[index].namaBarang << endl;
        cout << " > Stok Unit : " << stokBarang[index] << endl;
        cout << "-----------------------------------------------\n";
    }
    else
    {
        cout << "\n [!] Error: Kode Barang Tidak Ditemukan.\n";
        cout << "-----------------------------------------------\n";
    }
}

/**
 * KONSEP 4: Sorting (Bubble Sort)
 * Merapikan susunan barang berdasarkan abjad nama.
 */
void urutkanBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang == 0)
    {
        cout << " [!] Peringatan: Tidak dapat merapikan rak, stok gudang sedang kosong!\n";
        return;
    }
    if (totalBarang <= 1) return;

    for (int i = 0; i < totalBarang - 1; i++)
    {
        for (int j = 0; j < totalBarang - i - 1; j++)
        {
            if (daftarBarang[j].namaBarang > daftarBarang[j + 1].namaBarang)
            {
                // Swap Struct
                Barang tempB = daftarBarang[j];
                daftarBarang[j] = daftarBarang[j + 1];
                daftarBarang[j + 1] = tempB;

                // Swap Parallel Array (Stok)
                int tempS = stokBarang[j];
                stokBarang[j] = stokBarang[j + 1];
                stokBarang[j + 1] = tempS;
            }
        }
    }
    cout << " [v] Berhasil: Daftar barang telah dirapikan (A-Z).\n";
    simpanKeFile(daftarBarang, stokBarang, totalBarang); // Simpan perubahan
}

/**
 * OPERASI: BARANG KELUAR (Pengiriman Item)
 * Mencari barang berdasarkan kode dan mengulangi stoknya.
 * Jika stok habis, item akan dihapus dari daftar otomatis.
 */
void ambilBarang(Barang daftarBarang[], int stokBarang[], int *totalBarang)
{
    if (*totalBarang == 0)
    {
        cout << " [!] Gagal: Tidak ada stok untuk dikeluarkan.\n";
        return;
    }
    tampilBarang(daftarBarang, stokBarang, *totalBarang);

    cout << "\n===============================================\n";
    cout << "        PROSES: PENGELUARAN BARANG             \n";
    cout << "===============================================\n";
    cout << " [1] Ambil Barang Tertentu (per Kode)           \n";
    cout << " [2] Kosongkan Seluruh Stok Gudang             \n";
    cout << "-----------------------------------------------\n";
    int subPilihan;
    cout << " Pilih Sub-Operasi : ";
    cin >> subPilihan;

    if (subPilihan == 2)
    {
        char yakin;
        cout << "\n [!] PERINGATAN: Kosongkan seluruh stok gudang? (y/n): ";
        cin >> yakin;
        if (yakin == 'y' || yakin == 'Y')
        {
            *totalBarang = 0;
            cout << " [v] Berhasil: Seluruh stok gudang telah dibersihkan.\n";
            simpanKeFile(daftarBarang, stokBarang, *totalBarang);
        }
        else
        {
            cout << " [!] Dibatalkan: Stok gudang tetap aman.\n";
        }
    }
    else if (subPilihan == 1)
    {
        int code;
        cout << " Masukkan Code Barang : ";
        cin >> code;

        int indexFound = cariIndeksBerdasarkanCode(daftarBarang, *totalBarang, code);

        if (indexFound == -1)
        {
            cout << "\n [!] Error: Kode Barang Tidak Ditemukan.\n";
            return;
        }

        int jumlah;
        cout << " Nama Item  : " << daftarBarang[indexFound].namaBarang << endl;
        cout << " Stok Ready : " << stokBarang[indexFound] << endl;
        cout << " Ambil Jumlah : ";
        cin >> jumlah;

        if (jumlah > stokBarang[indexFound])
        {
            cout << "\n [!] Error: Stok tidak mencukupi.\n";
        }
        else
        {
            stokBarang[indexFound] -= jumlah;
            cout << "\n [v] Berhasil mengambil barang.\n";
            
            if (stokBarang[indexFound] <= 0)
            {
                cout << " [!] Info: Stok habis, item dihapus dari daftar gudang.\n";
                // SHIFTING
                for (int i = indexFound; i < *totalBarang - 1; i++)
                {
                    daftarBarang[i] = daftarBarang[i + 1];
                    stokBarang[i] = stokBarang[i + 1];
                }
                (*totalBarang)--;
            }
            simpanKeFile(daftarBarang, stokBarang, *totalBarang); // Simpan perubahan
        }
    }
    else
    {
        cout << " [!] Pilihan tidak valid!\n";
    }
}

int main()
{
    srand(time(0));
    
    int pilihan;
    // KONSEP 1: Array (Static Allocation 1000)
    Barang daftarBarang[1000]; 
    int stokBarang[1000];    
    int totalBarang = 0; 

    // Muat data lama saat program dimulai
    muatDariFile(daftarBarang, stokBarang, &totalBarang);

    do
    {
        cout << "===============================================\n";
        cout << "        SISTEM MANAJEMEN GUDANG LOGISTIK       \n";
        cout << "        (MANAJEMEN BARANG MASUK/KELUAR)        \n";
        cout << "===============================================\n";
        cout << " [1] Penerimaan Barang (Barang Masuk)          \n";
        cout << " [2] Cek Stok Gudang  (Laporan Stok)           \n";
        cout << " [3] Pengeluaran Barang (Barang Keluar)        \n";
        cout << " [4] Pencarian Item (Berdasarkan Kode)         \n";
        cout << " [5] Rapikan Rak (Sorting A-Z)                 \n";
        cout << " [6] Tutup Gudang & Selesai                    \n";
        cout << "===============================================\n";
        cout << " Choose Operation : ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer agar getline tidak terlewat

        switch (pilihan)
        {
        case 1:
            if (totalBarang < 1000)
                tambahBarang(daftarBarang, stokBarang, &totalBarang);
            else
                cout << "\n Peringatan: Slot Antrian Penuh!\n";
            break;
        case 2:
            tampilBarang(daftarBarang, stokBarang, totalBarang);
            break;
        case 3:
            ambilBarang(daftarBarang, stokBarang, &totalBarang);
            break;
        case 4:
            cariBarang(daftarBarang, stokBarang, totalBarang);
            break;
        case 5:
            urutkanBarang(daftarBarang, stokBarang, totalBarang);
            break;
        case 6:
            cout << "\n [!] Terimakasih. Sesi Gudang Berakhir.\n";
            simpanKeFile(daftarBarang, stokBarang, totalBarang); // Simpan terakhir kali
            break;
        default:
            cout << "\n [!] Pilihan tidak valid!\n";
            break;
        }

        if (pilihan != 6) {
            cout << "\n Tekan ENTER untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        }
    } while (pilihan != 6);

    system("cls"); // Bersihkan terminal saat benar-benar selesai
    return 0;
}
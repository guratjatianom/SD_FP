/**
 * PROJECT: SISTEM GUDANG LOGISTIK (QUEUE-BASED)
 * KONSEP STRUKTUR DATA YANG DIGUNAKAN:
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

/**
 * IMPLEMENTASI KONSEP QUEUE: ENQUEUE (Tambah Barang)
 * Barang baru selalu ditambahkan di posisi paling belakang (Indeks Rear).
 * KONSEP 5: Pointer (int *totalBarang)
 */
void tambahBarang(Barang daftarBarang[], int stokBarang[], int *totalBarang)
{
    int stokSekarang = hitungTotalStok(stokBarang, *totalBarang);
    
    if (stokSekarang >= 1000) {
        cout << "Gagal! Gudang (Queue) sudah penuh (Maks 1000 unit).\n";
        return;
    }

    cout << "\n=== Enqueue (Tambah Data Barang) ===\n";
    cout << "Kapasitas saat ini: " << stokSekarang << " / 1000\n";
    cout << "Antrian terisi   : " << *totalBarang << " jenis barang\n";
    cout << "---------------------------\n";

    string nama;
    int jumlah;

    cin.ignore();
    cout << "Nama Barang : ";
    getline(cin, nama);

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
    cout << "Barang masuk ke antrian gudang.\n";
}

// Menampilkan seluruh data dalam antrian
void tampilBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang == 0)
    {
        cout << "Antrian gudang kosong!\n";
        return;
    }
    cout << "\n=== Daftar Antrian Gudang ===\n";
    for (int i = 0; i < totalBarang; i++)
    {
        cout << i + 1 << ". Nama : " << daftarBarang[i].namaBarang 
             << " | Code : " << daftarBarang[i].codeBarang 
             << " | Jumlah : " << stokBarang[i] << endl;
    }
}

// KONSEP 3: Searching (Cari Barang)
void cariBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang == 0) return;

    int code;
    cout << "Masukkan Code Barang : ";
    cin >> code;

    int index = cariIndeksBerdasarkanCode(daftarBarang, totalBarang, code);

    if (index != -1)
    {
        cout << "\n=== Hasil Pencarian ===\n";
        cout << "Nama: " << daftarBarang[index].namaBarang << " | Stok: " << stokBarang[index] << endl;
    }
    else
    {
        cout << "Barang tidak ditemukan.\n";
    }
}

/**
 * KONSEP 4: Sorting (Bubble Sort)
 * Mengurutkan antrian berdasarkan abjad tanpa mengubah nilai stok.
 */
void urutkanBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
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
    cout << "Antrian berhasil diurutkan A-Z.\n";
}

/**
 * IMPLEMENTASI KONSEP QUEUE: DEQUEUE (Ambil Barang)
 * Modifikasi Queue: Mengambil barang tertentu (Searchable Queue).
 * Jika stok habis, dilakukan shifting untuk menjaga kontinuitas antrian.
 */
void ambilBarang(Barang daftarBarang[], int stokBarang[], int *totalBarang)
{
    if (*totalBarang == 0)
    {
        cout << "Antrian kosong.\n";
        return;
    }

    int code;
    cout << "Masukkan Code Barang untuk Dequeue : ";
    cin >> code;

    int indexFound = cariIndeksBerdasarkanCode(daftarBarang, *totalBarang, code);

    if (indexFound == -1)
    {
        cout << "Barang tidak ditemukan.\n";
        return;
    }

    int jumlah;
    cout << "Stok: " << stokBarang[indexFound] << "\nAmbil berapa : ";
    cin >> jumlah;

    if (jumlah > stokBarang[indexFound])
    {
        cout << "Stok tidak cukup.\n";
    }
    else
    {
        stokBarang[indexFound] -= jumlah;
        cout << "Berhasil mengambil barang.\n";

        if (stokBarang[indexFound] <= 0)
        {
            cout << "Item keluar dari antrian (Stok Habis).\n";
            // SHIFTING: Menjaga struktur antrian tetap rapat
            for (int i = indexFound; i < *totalBarang - 1; i++)
            {
                daftarBarang[i] = daftarBarang[i + 1];
                stokBarang[i] = stokBarang[i + 1];
            }
            (*totalBarang)--;
        }
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

    do
    {
        cout << "\n=== MENU GUDANG (ADJUSTED QUEUE) ===\n";
        cout << "1. Enqueue (Tambah Barang)\n";
        cout << "2. Tampilkan Antrian\n";
        cout << "3. Dequeue (Ambil Barang)\n";
        cout << "4. Searching (Cari Barang)\n";
        cout << "5. Sorting (Urutkan A-Z)\n";
        cout << "6. Keluar\n";
        cout << "Pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            if (totalBarang < 1000)
                tambahBarang(daftarBarang, stokBarang, &totalBarang); // Pointer concepts
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
            cout << "Keluar program.\n";
            break;
        }
    } while (pilihan != 6);

    return 0;
}
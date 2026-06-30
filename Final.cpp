#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * STRUKTUR DATA: Parallel Arrays
 * Program ini menggunakan dua array yang bekerja secara sejajar (parallel).
 * 1. daftarBarang[]: Menyimpan informasi dasar (Nama, Kode).
 * 2. stokBarang[]: Menyimpan jumlah unit barang.
 * Indeks 'i' pada daftarBarang berkaitan langsung dengan indeks 'i' pada stokBarang.
 */

struct Barang
{
    string namaBarang;
    int codeBarang;
};

// Fungsi pembantu untuk mencari barang berdasarkan code
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

// Fungsi pembantu untuk memastikan Kode Barang selalu unik di dalam gudang
bool cekCodeExist(Barang daftarBarang[], int totalBarang, int code)
{
    // Menggunakan fungsi cari indeks, jika ketemu (!= -1) berarti exist
    return cariIndeksBerdasarkanCode(daftarBarang, totalBarang, code) != -1;
}

// Fungsi untuk menjumlahkan seluruh unit barang yang ada di gudang
// Digunakan untuk mengecek kapasitas total gudang (maksimal 1000)
int hitungTotalStok(int stokBarang[], int totalBarang)
{
    int total = 0;
    for (int i = 0; i < totalBarang; i++)
    {
        total += stokBarang[i];
    }
    return total;
}

// Fungsi pembantu untuk mencari barang berdasarkan nama (untuk merge stok)
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

// Prosedur untuk menambah data barang baru
// Menggunakan POINTER (int *totalBarang) untuk memenuhi konsep ke-5
void tambahBarang(Barang daftarBarang[], int stokBarang[], int *totalBarang)
{
    // 1. Cek apakah gudang sudah benar-benar penuh (total 1000 unit)
    // Menggunakan dereference (*) untuk mengambil nilai dari pointer
    int stokSekarang = hitungTotalStok(stokBarang, *totalBarang);
    
    if (stokSekarang >= 1000) {
        cout << "Gagal! Gudang sudah mencapai kapasitas maksimal (1000 barang).\n";
        return;
    }

    // TAMPILKAN KAPASITAS SISA agar user tahu berapa banyak yang bisa dimasukkan
    cout << "\n=== Tambah Data Barang ===\n";
    cout << "Kapasitas saat ini: " << stokSekarang << " / 1000\n";
    cout << "Slot tersisa     : " << 1000 - stokSekarang << " barang\n";
    cout << "---------------------------\n";

    string nama;
    int jumlah;

    cin.ignore();
    cout << "Nama Barang : ";
    getline(cin, nama);

    // 2. CEK APAKAH BARANG SUDAH ADA (Berdasarkan Nama)
    // Jika ada, kita cukup menambah stoknya saja tanpa membuat entri baru
    int indexLama = cariIndeksBerdasarkanNama(daftarBarang, *totalBarang, nama);
    
    if (indexLama != -1) {
        cout << "PEMBERITAHUAN: Barang '" << nama << "' sudah terdaftar di gudang.\n";
        cout << "Code Barang : " << daftarBarang[indexLama].codeBarang << endl;
        cout << "Stok saat ini : " << stokBarang[indexLama] << endl;
        
        cout << "Masukkan jumlah tambahan : ";
        cin >> jumlah;

        // Validasi kapasitas total meskipun hanya menambah stok barang lama
        if (stokSekarang + jumlah > 1000) {
            cout << "Gagal! Tambahan stok melebihi kapasitas sisa gudang.\n";
            cout << "Kapasitas tersisa: " << 1000 - stokSekarang << " barang.\n";
            return;
        }

        stokBarang[indexLama] += jumlah;
        cout << "Stok '" << nama << "' berhasil diperbarui.\n";
        return; // SELESAI: Keluar dari fungsi agar tidak membuat entri baru di bawah
    }
    
    // 3. GENERASI KODE UNIK OTOMATIS (Hanya untuk barang yang benar-benar baru)
    int generatedCode;
    do {
        generatedCode = rand() % 9000 + 1000; // Angka acak 4 digit (1000-9999)
    } while (cekCodeExist(daftarBarang, *totalBarang, generatedCode));

    cout << "Code Barang (Otomatis) : " << generatedCode << endl;

    cout << "Jumlah Barang : ";
    cin >> jumlah;

    // 4. VALIDASI KAPASITAS SISA
    if (stokSekarang + jumlah > 1000) {
        cout << "Gagal! Jumlah barang melebihi kapasitas sisa gudang.\n";
        cout << "Kapasitas tersisa: " << 1000 - stokSekarang << " barang.\n";
        return;
    }

    // Memasukkan data ke array pada indeks totalBarang saat ini
    daftarBarang[*totalBarang].namaBarang = nama;
    daftarBarang[*totalBarang].codeBarang = generatedCode;
    stokBarang[*totalBarang] = jumlah;

    // Tambahkan counter total jenis barang (menggunakan dereference pointer)
    (*totalBarang)++;
    cout << "Barang berhasil ditambahkan sebagai item baru.\n";
}

// Prosedur untuk menampilkan seluruh isi gudang
void tampilBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang == 0)
    {
        cout << "Gudang masih kosong!\n";
        return;
    }
    cout << "\n=== Daftar Barang di Gudang ===\n";
    for (int i = 0; i < totalBarang; i++)
    {
        // i+1 digunakan agar tampilan nomor urut mulai dari 1 (user friendly)
        cout << i + 1 << ". Nama barang   : " << daftarBarang[i].namaBarang << endl;
        cout << "   Code barang   : " << daftarBarang[i].codeBarang << endl;
        cout << "   Jumlah barang : " << stokBarang[i] << endl;
        cout << "---------------------------\n";
    }
}

// Prosedur untuk mencari barang berdasarkan code
// Merupakan implementasi konsep SEARCHING
void cariBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang == 0)
    {
        cout << "Gudang masih kosong!\n";
        return;
    }

    int code;
    cout << "Masukkan Code Barang yang ingin dicari : ";
    cin >> code;

    // Menggunakan helper function untuk mencari indeks
    int index = cariIndeksBerdasarkanCode(daftarBarang, totalBarang, code);

    if (index != -1)
    {
        cout << "\n=== Hasil Pencarian ===\n";
        cout << "Nama barang   : " << daftarBarang[index].namaBarang << endl;
        cout << "Code barang   : " << daftarBarang[index].codeBarang << endl;
        cout << "Jumlah barang : " << stokBarang[index] << endl;
        cout << "-----------------------\n";
    }
    else
    {
        cout << "Barang dengan code " << code << " tidak ditemukan.\n";
    }
}

/**
 * IMPLEMENTASI KONSEP SORTING: Bubble Sort
 * Mengurutkan barang berdasarkan abjad (Nama Barang).
 * Karena menggunakan parallel array, maka stokBarang juga ikut di-swap saat mengganti daftarBarang.
 */
void urutkanBarang(Barang daftarBarang[], int stokBarang[], int totalBarang)
{
    if (totalBarang <= 1)
    {
        cout << "Tidak cukup data untuk mengurutkan.\n";
        return;
    }

    for (int i = 0; i < totalBarang - 1; i++)
    {
        for (int j = 0; j < totalBarang - i - 1; j++)
        {
            // Sorting alfabetis A-Z
            if (daftarBarang[j].namaBarang > daftarBarang[j + 1].namaBarang)
            {
                // Swap Nama & Code (Struct)
                Barang tempB = daftarBarang[j];
                daftarBarang[j] = daftarBarang[j + 1];
                daftarBarang[j + 1] = tempB;

                // Swap Stok (juga di-swap agar parallel array konsisten)
                int tempS = stokBarang[j];
                stokBarang[j] = stokBarang[j + 1];
                stokBarang[j + 1] = tempS;
            }
        }
    }
    cout << "Gudang berhasil diurutkan berdasarkan abjad (A-Z).\n";
}

// Prosedur untuk mengambil/mengurangi barang
// Menggunakan POINTER (int *totalBarang)
void ambilBarang(Barang daftarBarang[], int stokBarang[], int *totalBarang)
{
    if (*totalBarang == 0)
    {
        cout << "Gudang kosong, tidak ada barang yang bisa diambil.\n";
        return;
    }

    int code;
    cout << "Masukkan Code Barang yang akan diambil : ";
    cin >> code;

    // 1. SEARCHING: Mencari indeks barang berdasarkan kode
    int indexFound = cariIndeksBerdasarkanCode(daftarBarang, *totalBarang, code);

    if (indexFound == -1)
    {
        cout << "Barang dengan code " << code << " tidak ditemukan.\n";
        return;
    }

    int jumlahAmbil;
    cout << "Stok saat ini: " << stokBarang[indexFound] << endl;
    cout << "Masukkan jumlah yang akan diambil : ";
    cin >> jumlahAmbil;

    // 2. VALIDASI JUMLAH
    if (jumlahAmbil > stokBarang[indexFound])
    {
        cout << "Gagal! Jumlah yang diambil melebihi stok yang ada.\n";
    }
    else
    {
        stokBarang[indexFound] -= jumlahAmbil;
        cout << "Berhasil mengambil " << jumlahAmbil << " unit " << daftarBarang[indexFound].namaBarang << ".\n";

        // 3. PENGHAPUSAN DATA (Jika Stok Habis)
        // Jika stok menjadi 0, kita menghapus item dengan cara SHIFTING (menggeser elemen)
        if (stokBarang[indexFound] == 0)
        {
            cout << "Stok habis, barang '" << daftarBarang[indexFound].namaBarang << "' dihapus dari daftar.\n";
            // Elemen dari indexFound+1 digeser ke depan (menutup celah yang kosong)
            for (int i = indexFound; i < *totalBarang - 1; i++)
            {
                daftarBarang[i] = daftarBarang[i + 1];
                stokBarang[i] = stokBarang[i + 1];
            }
            // Kurangi jumlah jenis barang melalui dereference pointer
            (*totalBarang)--;
        }
    }
}

int main()
{
    srand(time(0)); // Seed random agar angka yang di-generate selalu berbeda tiap program dijalankan
    
    int pilihan;
    // DEKLARASI ARRAY: Konsep ke-1
    Barang daftarBarang[1000]; 
    int stokBarang[1000];    
    int totalBarang = 0; 

    do
    {
        cout << "\n=== Menu Gudang ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Ambil Barang\n";
        cout << "4. Cari Barang\n";
        cout << "5. Urutkan Barang (A-Z)\n";
        cout << "6. Keluar\n";
        cout << "Masukkan Pilihan (1-6): ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            // Pastikan tidak melebihi batas indeks array (1000 slot)
            if (totalBarang < 1000)
            {
                // Menggunakan '&' untuk mengirim alamat memori (PASS BY POINTER)
                tambahBarang(daftarBarang, stokBarang, &totalBarang);
            }
            else
            {
                cout << "Gudang sudah penuh (batas slot jenis barang tercapai)!\n";
            }
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
            cout << "Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
        }
    } while (pilihan != 6);

    return 0;
}
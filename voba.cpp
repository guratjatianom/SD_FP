#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    int umur;
};

// Fungsi menerima struct secara "Pass by Value"
void cetakMahasiswa(Mahasiswa m) {
    cout << "Nama: " << m.nama << ", Umur: " << m.umur << endl;
    m.umur = 25; // Ini hanya mengubah salinan di dalam fungsi
}

int main() {
    Mahasiswa mhs1 = {"Budi", 20};
    
    // Memanggil fungsi
    cetakMahasiswa(mhs1); 
    
    // Umur mhs1 tetap 20, tidak berubah jadi 25
    cout << "Umur asli: " << mhs1.umur << endl; 
    return 0;
}
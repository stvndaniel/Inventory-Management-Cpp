#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct barang {
    static const int maxbarang = 100;
    string nama;
    int id, stok;
    double harga;
};


void tambahbarang(barang* inventory, int& jumlahbarang) {
    if (jumlahbarang >= barang::maxbarang) {
        cout << "Inventory penuh, tidak bisa menambah barang.\n";
        return;
    }
        cin.ignore();
        cout << "Masukkan Nama Barang   : ";
        getline(cin, inventory[jumlahbarang].nama);
        cout << "Masukkan ID Barang     : ";
        cin >> inventory[jumlahbarang].id;
        cout << "Masukkan Stok Barang   : ";
        cin >> inventory[jumlahbarang].stok;
        cout << "Masukkan Harga Barang  : ";
        cin >> inventory[jumlahbarang].harga;
        
    ofstream file("inventory.txt", ios::app);
        if (file.is_open()){
        file << "\nNama Barang    : " << inventory[jumlahbarang].nama << endl
             << "ID Barang      : " << inventory[jumlahbarang].id << endl
             << "Stok Barang    : " << inventory[jumlahbarang].stok << endl
             << "Harga Barang   : " << inventory[jumlahbarang].harga << endl;

    }
    file.close();
    jumlahbarang++;

    char lanjut;
    cout << "Apakah ingin menambahkan barang lagi?(y/n)";
    cin >> lanjut;

    if (lanjut == 'y' || lanjut == 'Y') {
        tambahbarang(inventory, jumlahbarang);
    }else {
        cout << "Barang berhasil ditambah!\n";
    }
}

void tampilkanbarang(barang* inventory, int& jumlahbarang) {
    ifstream file("inventory.txt");
    string line;
    while (getline(file, line))
        {
            cout << line << "\n";
        }
}

int caribarang(barang* inventory, int jumlahbarang, int id) {
        for(int i = 0; i < jumlahbarang; i++){
            if (inventory[i].id == id) {
                return i;
            }
        }
        return -1;
    }

void jualbarang(barang* inventory, int& jumlahbarang) {
    int id, jumlah;
    cout << "Masukkan ID Barang yang akan dijual : ";
    cin >> id;
    cout << "Masukkan Jumlah Barang yang akan dijual : ";
    cin >> jumlah;

    int index = caribarang(inventory, jumlahbarang, id);
    if (index != -1) {
        if (inventory[index].stok >= jumlah) {
            inventory[index].stok -= jumlah;
            double totalharga = jumlah * inventory[index].harga;
            cout << "-----Penjualan Berhasil-----\n";
            cout << "Total Harga : " << totalharga << endl;
        
        ofstream file("inventory.txt", ios::app);
            if (file.is_open()) {
                file << "\nNama Barang    : " << inventory[index].nama << endl
                     << "ID Barang      : " << inventory[index].id << endl
                     << "Stok Barang    : " << inventory[index].stok << endl
                     << "Harga Barang   : " << inventory[index].harga << endl;
                file.close();
            } 
        } else {
            cout << "Stok tidak mencukupi!\n";
        }
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}


void backupdata(barang* inventory, int jumlahbarang) { 
    ofstream file("backupdata.txt", ios::app); 
    if (file.is_open()) { 
        for (int i = 0; i < jumlahbarang; i++) 
        { file << "\nNama Barang      : " << inventory[i].nama << endl
               << "ID Barang        : " << inventory[i].id << endl
               << "Stok Barang      : " << inventory[i].stok << endl 
               << "Harga Barang     : " << inventory[i].harga << endl; 
        } 
        file.close();
    }
}

void hapusbarang(barang* inventory, int& jumlahbarang){
    int id;
    cout<<"Masukkan ID Barang yang akan dihapus : ";
    cin>>id;

    int index = caribarang(inventory, jumlahbarang, id);
    if(index != -1){
        backupdata(&inventory[index],1);
        for(int i = index; i < jumlahbarang - 1; i++){
            inventory[i] = inventory[i+1];
        }
        jumlahbarang--;
        cout << "Barang berhasil dihapus!\n";
            ofstream file("inventory.txt", ios_base::trunc);
            if (file.is_open()){
                for(int i = 0; i < jumlahbarang; i++){
                    file << "\nNama Barang    : " << inventory[i].nama << endl
                         << "ID Barang      : " << inventory[i].id << endl
                         << "Stok Barang    : " << inventory[i].stok << endl
                         << "Harga Barang   : " << inventory[i].harga << endl;
                }
            }
            file.close();
        }else{
            cout << "Barang tidak ditemukan.\n";
    }
}

/*void restorebarang(barang* inventory, int& jumlahbarang) {
    ifstream backupfile("backupdata.txt");
    if (!backupfile.is_open()) {
        cout << "Backup data tidak ditemukan.\n";
        return;
    }
    barang temp;
    bool found = false;
    int id;
    cout << "Masukkan ID Barang yang akan direstore: ";
    cin >> id;
    
    while (backupfile >> temp.nama >> temp.id >> temp.stok >> temp.harga) {
        if (temp.id == id) {
            if (jumlahbarang >= barang::maxbarang) {
                cout << "Inventory penuh!\n";
                return;
            }
            inventory[jumlahbarang++] = temp;
            found = true;
            backupdata.close();
            break;
        }
    }
    backupfile.close();

    if (found) {
        ofstream inventoryfile("inventory.txt", ios::trunc);
        if (inventoryfile.is_open()) {
            for (int i = 0; i < jumlahbarang; i++) {
                inventoryfile << inventory[i].nama << endl
                               << inventory[i].id << endl
                               << inventory[i].stok << endl
                               << inventory[i].harga << endl;
            }
            inventoryfile.close();
        }
        cout << "Barang berhasil direstore!\n";
    } else {
        cout << "Barang dengan ID " << id << " tidak ditemukan dalam backup.\n";
    }
}*/

void restorebarang(barang* inventory, int& jumlahbarang) {
    ifstream backupfile("backupdata.txt");
    if (!backupfile.is_open()) {
        cout << "Backup data tidak ditemukan.\n";
        return;
    }

    string line;
    bool found = false;
    int id;
    cout << "Masukkan ID Barang yang akan direstore: ";
    cin >> id;

    while (getline(backupfile, line)) {
        barang temp;
        // Parsing data dari line
        if (line.find("ID Barang") != string::npos) {
            // Ambil ID Barang
            sscanf(line.c_str(), "ID Barang      : %d", &temp.id);
            getline(backupfile, line); // Baca Nama Barang
            sscanf(line.c_str(), "Nama Barang    : %d", &temp.nama[0]);
            getline(backupfile, line); // Baca Stok Barang
            sscanf(line.c_str(), "Stok Barang    : %d", &temp.stok);
            getline(backupfile, line); // Baca Harga Barang
            sscanf(line.c_str(), "Harga Barang   : %d", &temp.harga);
            
            if (temp.id == id) {
                if (jumlahbarang >= barang::maxbarang) {
                    cout << "Inventory penuh!\n";
                    backupfile.close();
                    return;
                }
                inventory[jumlahbarang++] = temp;
                found = true;
                break;
            }
        }
    }
    backupfile.close();

    if (found) {
        ofstream inventoryfile("inventory.txt", ios::trunc);
        if (inventoryfile.is_open()) {
            for (int i = 0; i < jumlahbarang; i++) {
                inventoryfile  << "\nNama Barang    : " << inventory[i].nama << endl
                               << "ID Barang      : " << inventory[i].id << endl
                               << "Stok Barang    : " << inventory[i].stok << endl
                               << "Harga Barang   : " << inventory[i].harga << endl
                               << "------------------------" << endl; // Separator untuk kejelasan
            }
            inventoryfile.close();
        } else {
            cout << "Gagal membuka file inventory untuk menulis." << endl;
        }
        cout << "Barang berhasil direstore!\n";
    } else {
        cout << "Barang dengan ID " << id << " tidak ditemukan dalam backup.\n";
    }
}


void tampilkanmenu() {
    cout << "===============================\n"
         << "|    Sistem Inventory Toko    |\n"
         << "===============================\n"
         << "| 1. Tambah Barang            |\n"
         << "| 2. Tampilkan Barang         |\n"
         << "| 3. Jual Barang              |\n"
         << "| 4. Hapus Barang             |\n"
         << "| 5. Restore Barang           |\n"
         << "===============================\n";
};

void pilihmenu() {
    static const int maxbarang = 100;
    int jumlahbarang = 0;
    int pilihan;
    barang inventory[barang::maxbarang];
    do{
        tampilkanmenu();
        cout << "Pilih Menu : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahbarang(inventory, jumlahbarang);
            break;
        case 2:
            tampilkanbarang(inventory, jumlahbarang);
            break;
        case 3:
            jualbarang(inventory, jumlahbarang);
            break;
        case 4:
            hapusbarang(inventory, jumlahbarang);
            break;
        case 5:
            restorebarang(inventory, jumlahbarang);
            break;   
        default:
            cout << "Pilihan Tidak Valid.\n";
            break;
        }
    }while (pilihan != 6);
}

int main() {
    pilihmenu();
    return 0;
}
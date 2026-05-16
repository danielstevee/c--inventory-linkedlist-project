#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct barang {
    string name, idbrg, harga, stok;
    barang *next;
    barang *prev; 
};

struct keranjang {
    string idBarang, namaBarang;
    int harga, quantity;
    keranjang *next;
    keranjang(string idBarang, string namaBarang, int harga, int quantity) {
        this->idBarang = idBarang;
        this->namaBarang = namaBarang;
        this->harga = harga;
        this->quantity = quantity;
        this->next = nullptr;
    }
};

struct pesanan {
    string userID, username, alamat;
    keranjang *barang;
    pesanan *next;
    pesanan *prev;
    string status;
    pesanan(string userID, string username, string alamat, keranjang *barang) {
        this->userID = userID;
        this->username = username;
        this->alamat = alamat;
        this->barang = barang;
        this->next = nullptr;
        this->prev = nullptr;
        this->status = "Menunggu Pembayaran";
    }
};

struct user {
    string username, userID, password, role, tanggallahir, alamat;
    user *next;
    keranjang *keranjangHead;
    user(string username, string password, string role, string tanggallahir, string alamat = ""){
        this->username = username;
        this->password = password;
        this->role = role;
        this->tanggallahir = tanggallahir;
        this->alamat = alamat;
        this->next = nullptr;
        this->keranjangHead = nullptr;
    }
};

struct riwayatPesanan {
    string userID;
    string username;
    string alamat;
    keranjang *barang;
    string status;
    riwayatPesanan *next;
    riwayatPesanan(string userID, string username, string alamat, keranjang *barang, string status) {
        this->userID = userID;
        this->username = username;
        this->alamat = alamat;
        this->barang = barang;
        this->status = status;
        this->next = nullptr;
    }
};




barang *Data = nullptr; 
barang *tail = nullptr;
user *userlist = nullptr;
pesanan *front = nullptr;
pesanan *rear = nullptr;
riwayatPesanan *riwayatFront = nullptr; 


void lihatPesananAdmin(pesanan *&front);
void lihatRiwayatPesananAdmin();
void lihatPesananSayaCustomer(user *currentUser );
void lihatRiwayatPesananCustomer(user *currentUser);
void tambahbarang();
void admin();
void checkout(pesanan *&front, pesanan *&rear, string userID, string username, string alamat, keranjang *&keranjangHead);
void updateRiwayatPesanan (string userID, string username, string alamat, keranjang *barang, string status);
string createIDbrg() {
    string id = "";
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        id += to_string(rand() % 10);
    }
    return id;
}

void insertbarang(barang *&head, barang *&tail, string name, string harga, string stok){
    barang *newBarang = new barang;

    newBarang->name = name;
    newBarang->idbrg = createIDbrg();
    newBarang->harga = harga;
    newBarang->stok = stok;
    newBarang->next = nullptr;
    newBarang->prev = nullptr;

    if (head == nullptr) 
    {
        head = newBarang; 
        tail = newBarang;
        head->next = head;
        head->prev = head;
        tail->next = tail;
        tail->prev = tail;
    } 
    else 
    { 
        tail->next = newBarang;
        newBarang->prev = tail;
        tail = newBarang;
    }
    cout << "\n ------ Tambah Barang ------\n"
         << " "<< name << " Berhasil ditambahkan!\n"
         << " ID Barang : " << newBarang->idbrg << endl;
}

void enqueue(pesanan *&front, pesanan *&rear, string userID, string username, string alamat, keranjang *barang) {
    pesanan *newPesanan = new pesanan(userID, username, alamat, barang);
    if (rear == nullptr) {
        front = rear = newPesanan;
    } else {
        rear->next = newPesanan;
        newPesanan->prev = rear; // Hubungkan dengan prev
        rear = newPesanan;
    }
    cout << "Pesanan berhasil ditambahkan ke antrian.\n";
}

void createID(user &people, int role) {
    string peopleID;

    char first;
    first = toupper(people.username.front());
    peopleID = to_string(((int)first-'A'+1) % 10);
    first = toupper(people.username.back());
    peopleID += to_string(((int)first-'A'+1) % 10);

    int index = 0;
    string people2 = "";
    int total = 0;
    for (char ch : people.tanggallahir) {
        if (ch == '-' || ch == '/') {
            total += stoi(people2);
            people2 = "";
        } else {
            people2 += ch;
        }
        if (index == people.tanggallahir.length()-1) {
            total += stoi(people2);
        }
        index++;
    }
    peopleID += to_string(total % 10);

    index = 0;
    int counter = 0;
    for (char temp : people.password) {
        if (counter == 2) {
            break;
        } else if (temp >= '0' && temp <= '9') {
            peopleID += temp;
            counter++;
        }
        index++;
    }
    if (index == people.password.length() && counter == 1){
        peopleID += '0';
    }
    peopleID += to_string(role);
    people.userID = peopleID;
}

void daftarbarang() {
    if (Data == nullptr) {
        cout << "------Daftar Barang------\n";
        cout << " barang tidak tersedia\n";
        cout << " Apakah Anda ingin menambahkan barang? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            tambahbarang();
        } else {
            return;
        }
    } else {
        barang *current = Data;
        cout << "------Daftar Barang------\n";
        while (current != nullptr) {
            cout << "===============================\n";
            cout << " Nama  : " << current->name << endl 
                 << " ID    : " << current->idbrg << endl 
                 << " Harga : " << current->harga << endl 
                 << " Stok  : " << current->stok << endl
                 << "===============================\n";
            current = current->next;
        }
        cout << " Tekan enter untuk kembali ke menu admin";
        cin.ignore();
        cin.get();
    }
}

void tambahbarang() {
    do {
        string name, idbrg, harga, stok;
        cout << " ------ Tambah Barang ------\n"
             << " ===========================\n";
        cout << " Nama Barang   : ";
        cin.ignore();
        getline(cin,name);
        cout << " Harga Barang  : ";
        cin >> harga;
        cout << " Stok Barang   : ";
        cin >> stok;
        cout << " ===========================\n";
        
        insertbarang(Data, tail, name, harga, stok);
            
        cout << " Apakah Anda ingin menambahkan barang lain? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            break;
        }
    } while (true);
}


void lihatPesananAdmin(pesanan *&front) {
    if (front == nullptr) {
        cout << "Tidak ada pesanan yang perlu diproses.\n";
        return;
    }

    pesanan *current = front;
    int choice; 
    int index = 1;

    do {
        cout << "================== Pesanan ke - " << index << " ==================\n";
        cout << "Nama   : " << current->username << endl;
        cout << "ID     : " << current->userID << endl;
        cout << "Alamat : " << current->alamat << endl;

        int totHarga = 0;
        keranjang *barang = current->barang;
        while (barang != nullptr) {
            cout << "=============================\n";
            cout << "Id     : " << barang->idBarang << endl;
            cout << "Nama   : " << barang->namaBarang << endl;
            cout << "Harga  : " << barang->harga << endl;
            cout << "Jumlah : " << barang->quantity << endl;
            totHarga += barang->harga * barang->quantity;
            barang = barang->next;
        }
        cout << "=============================\n";
        cout << "Total Harga: " << totHarga << endl;

        cout << "1. Setujui Pesanan\n"
             << "2. Tolak Pesanan\n" 
             << "3. Kembali ke Menu Admin\n"
             << "Pilihan Anda: ";
        cin >> choice;
        cout << "Pilihan diterima: " << choice << endl; // Debugging line
        if (choice == 1) { 
            current->status = "Pesanan Sedang dalam Proses Pengiriman"; 
            updateRiwayatPesanan(current->userID, current->username, current->alamat, current->barang, "Pesanan Sedang dalam Proses Pengiriman");
            cout << "Pesanan telah disetujui \n"; // Debugging line
            return;
        } 
        else if (choice == 2) { 
            current->status = "Pesanan dibatalkan oleh Admin"; 
            updateRiwayatPesanan(current->userID, current->username, current->alamat, current->barang, "Pesanan dibatalkan oleh Admin");
            cout << "Pesanan telah dibatalkan.\n"; // Debugging line
            return;
        }
        else if (choice == 3) {
            cout << "Kembali ke Menu Admin\n"; // Debugging line
            return; 
        } else {
            cout << "Pilihan tidak valid.\n"; // Debugging line
        }

        index++;
        current = current->next; 
    } while (current != nullptr);
}



void admin() {
    int pilihan;
    do {
        cout << " ------ Menu Admin ------\n"
             << " 1. Lihat Daftar Barang\n"
             << " 2. Tambah Barang\n"
             << " 3. Pesanan\n"
             << " 4. Riwayat Pesanan\n" // Opsi baru untuk riwayat pesanan
             << " 5. Logout\n"
             << " Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                daftarbarang();
                break;
            case 2:
                tambahbarang();
                break;
            case 3:
                lihatPesananAdmin(front);
                break; 
            case 4:
                lihatRiwayatPesananAdmin(); // Menampilkan riwayat pesanan
                break;
            case 5:
                return; 
            default:
                cout << " Pilihan tidak tersedia" << endl;
        }
    } while (true);
}


void updateRiwayatPesanan(string userID, string username, string alamat, keranjang *barang, string status) {
    riwayatPesanan *newRiwayat = new riwayatPesanan(userID, username, alamat, barang, status);
    
    newRiwayat->next = riwayatFront;
    riwayatFront = newRiwayat;
}

void lihatRiwayatPesananAdmin() {
    if (riwayatFront == nullptr) {
        cout << "Tidak ada lagi riwayat pesanan yang tersedia.\n";
        return;
    }

    riwayatPesanan *current = riwayatFront;
    bool adaPesanan = false;

    while (current != nullptr) {
        if (current->status == "Pesanan Telah Diterima" || current->status == "Pesanan dibatalkan oleh Admin") {
            adaPesanan = true;
            cout << "------ Riwayat Pembelian ------\n";
            cout << "Nama    : " << current->username << endl;
            cout << "ID      : " << current->userID << endl;
            cout << "Alamat  : " << current->alamat << endl;

            keranjang *barang = current->barang;
            int total = 0;
            while (barang != nullptr) {
                cout << "=============================\n";
                cout << "Id       : " << barang->idBarang << endl;
                cout << "Nama     : " << barang->namaBarang << endl;
                cout << "Harga    : " << barang->harga << endl;
                cout << "Quantity : " << barang->quantity << endl;
                total += barang->harga * barang->quantity;
                barang = barang->next;
            }
            cout << "=============================\n";
            cout << "Total    : " << total << endl;
            cout << "Status   : " << current->status << endl;

            cout << "Press any key to continue . . . ";
            cin.ignore();
            cin.get();
        }
        current = current->next;
    }

    if (!adaPesanan) {
        cout << "Tidak ada lagi riwayat pesanan yang tersedia.\n";
    }
}

void tambahKeKeranjang(keranjang *&head, string idBarang, string namaBarang, int harga, int quantity) {
    keranjang *newItem = new keranjang(idBarang, namaBarang, harga, quantity);
    newItem->next = head;
    head = newItem;
}

void daftarbarangcustomer(barang *head, keranjang *&keranjangHead) {
    if (Data == nullptr) {
        cout << " Tidak ada barang yang tersedia.\n";
    } else {
        barang *current = Data;
        char choice;
        do {
                cout << " ------ Daftar Barang------ \n";
                cout << "=============================\n";
                cout << " Nama: " << current->name << endl 
                     << " ID: " << current->idbrg<< endl 
                     << " Harga: " << current->harga << endl 
                     << " Stok: " << current->stok << endl;
                cout << "=============================\n"
                     << " 1. Next \n"
                     << " 2. Previous \n"
                     << " 3. Tambahkan ke keranjang\n"
                     << " 4. Keluar \n"
                     << " Pilihan: ";
                cin >> choice;
                if (choice == '1' && current->next != nullptr) {
                    current = current->next;
                } else if (choice == '2' && current->prev != nullptr) {
                    current = current->prev;
                } else if (choice == '3') {
                    int quantity;
                    cout << " Masukkan Jumlah: ";
                    cin >> quantity;
                    tambahKeKeranjang(keranjangHead, current->idbrg, current->name, stoi(current->harga), quantity);
                    cout << " Barang berhasil ditambahkan ke keranjang.\n";
                    break;
                } else if (choice == '4') {
                    break;
                } else {
                    cout << " Pilihan tidak tersedia atau tidak ada barang lagi\n";
                }
            } while (true);
        }
}

void caribarang(barang *head, keranjang *&keranjangHead) {
    if (tail == nullptr) {
        cout << " Tidak ada barang yang tersedia\n";
    } 
    else {
        string cariID;
        cout << "Masukkan ID/Nama Barang: ";
        cin.ignore();
        getline(cin, cariID);
    
        barang *current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->idbrg == cariID || current->name == cariID) {
                found = true;
                cout << "=============================\n";
                cout << " Id: " << current->idbrg << endl
                     << " Nama: " << current->name << endl
                     << " Harga: " << current->harga << endl
                     << " Stok: " << current->stok << endl;
                cout << " 1. Masukkan Ke Keranjang\n"
                     << " 2. Keluar\n "
                     << " Pilihan Anda: ";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    int quantity;
                    cout << " Masukkan Jumlah: ";
                    cin >> quantity;
                    tambahKeKeranjang(keranjangHead, current->idbrg, current->name, stoi(current->harga), quantity);
                    cout << "Barang berhasil ditambahkan ke keranjang.\n";
                }
                break;
            }
            current = current->next;
        }
            if (!found) {
            cout << "------Cari Barang------\n";
            cout << " Barang dengan ID " << cariID << " tersebut tidak ditemukan\n";
        }
    }
}


void lihatKeranjang(keranjang *head, user *currentUser) {
    if (head == nullptr) {
        cout << "Keranjang belanja kosong.\n";
        return;
    }

    keranjang *current = head;
    int total = 0;
    while (current != nullptr) {
        cout << "=============================\n";
        cout << "Id         : " << current->idBarang << endl
             << "Nama       : " << current->namaBarang << endl
             << "Harga      : " << current->harga << endl
             << "Quantity   : " << current->quantity << endl;
        total += current->harga * current->quantity;
        current = current->next;
    }
    cout << "=============================\n";
    cout << "Total: " << total << endl;

    cout << "1. Checkout\n"
         << "2. Lanjut Belanja\n"
         << "Pilihan Anda: ";
    int pilihanCO;
    cin >> pilihanCO;

    if (pilihanCO == 1) {
        checkout(front, rear, currentUser->userID, currentUser->username, currentUser->alamat, head);
    }
}

keranjang* cartToCheckout(keranjang *&keranjangHead, string id) {
    keranjang *curr = keranjangHead;
    keranjang *pesanan = nullptr;
    keranjang *tailPesanan = nullptr;

    if (id.length() >= 5) {
        string ids[id.length()/5]; // Asumsi maksimal 100 ID
        string dummy;
        int arrIndex = 0;
        for (char num : id) {
            if (isdigit(num)) {
                dummy += num;
            } else if (num == ',') {
                ids[arrIndex] = dummy;
                dummy = "";
                arrIndex++;
            }
        }
        if (!dummy.empty()) {
            ids[arrIndex] = dummy;
            arrIndex++;
        }

        for (int i = 0; i < arrIndex; i++) {
            curr = keranjangHead;
            keranjang *prev = nullptr;
            while (curr != nullptr) {
                if (curr->idBarang == ids[i]) {
                    // Pisahkan barang dari keranjang
                    if (prev == nullptr) {
                        keranjangHead = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    // Tambahkan ke list pesanan
                    if (pesanan == nullptr) {
                        pesanan = curr;
                        tailPesanan = curr;
                    } else {
                        tailPesanan->next = curr;
                        tailPesanan = curr;
                    }
                    curr->next = nullptr;
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    } else {
        cout << "=====================================\n"
             << "ID Salah\n"
             << "=====================================\n";
    }

    return pesanan;
}



void updateStock(barang* head, keranjang* cart) {
    while (cart != nullptr) {
        barang* current = head;
        while (current != nullptr) {
            if (current->idbrg == cart->idBarang) {
                int newStock = stoi(current->stok) - cart->quantity;
                current->stok = to_string(newStock);
                break;
            }
            current = current->next;
        }
        cart = cart->next;
    }
}



void checkout(pesanan *&front, pesanan *&rear, string userID, string username, string alamat, keranjang *&keranjangHead) {
    if (keranjangHead == nullptr) {
        cout << "Keranjang belanja kosong.\n";
        return;
    }

   
    string inputIDs;
    cout << "Masukkan ID barang yang ingin dicheckout (pisahkan dengan koma, contoh: 21547, 14867): ";
    cin.ignore(); 
    getline(cin, inputIDs);

    
    keranjang *barangCheckout = cartToCheckout(keranjangHead, inputIDs);

    if (barangCheckout == nullptr) {
        cout << "Tidak ada barang yang ditemukan dengan ID yang dimasukkan.\n";
        return;
    }

    
    cout << "\n------ Nota Pembelian ------\n";
    cout << " Nama  : " << username << endl;
    cout << " ID    : " << userID << endl;
    cout << " Alamat: " << alamat << endl;

    cout << "===================================\n";
    keranjang *current = barangCheckout;
    int totalHarga = 0;
    while (current != nullptr) {
        cout << " ID Barang  : " << current->idBarang << endl;
        cout << " Nama Barang: " << current->namaBarang << endl;
        cout << " Harga      : " << current->harga << endl;
        cout << " Quantity   : " << current->quantity << endl;
        cout << "===================================\n";
        totalHarga += current->harga * current->quantity;
        current = current->next;
    }
    
    cout << "\n Total Harga: " << totalHarga << endl;

    
    updateStock(Data, barangCheckout);

    
    enqueue(front, rear, userID, username, alamat, barangCheckout);

    riwayatPesanan *newRiwayat = new riwayatPesanan(userID, username, alamat, barangCheckout, "Pesanan Sedang dalam Proses Pengiriman");
    newRiwayat->next = riwayatFront;
    riwayatFront = newRiwayat;
    cout << " ------ Pesanan sedang diproses ------\n";
}


void customer(user *currentUser) {
    int pilihan;
    keranjang *&keranjangHead = currentUser->keranjangHead;

    do {
        cout << " ------ Menu Customer ------\n"
             << " 1. Lihat Daftar Barang\n"
             << " 2. Cari Barang\n"
             << " 3. Keranjang Belanja\n"
             << " 4. Pesanan Saya\n"  // Menambahkan opsi Pesanan Saya
             << " 5. Riwayat Pesanan\n" // Menambahkan opsi Riwayat Pesanan
             << " 6. Logout\n"
             << " Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                daftarbarangcustomer(Data, keranjangHead);
                break;
            case 2:
                caribarang(Data, keranjangHead);
                break;
            case 3:
                lihatKeranjang(keranjangHead, currentUser);
                break;
            case 4:
                lihatPesananSayaCustomer(currentUser);  // Menambahkan fungsi untuk melihat pesanan
                break;
            case 5:
                lihatRiwayatPesananCustomer(currentUser); // Menambahkan fungsi untuk melihat riwayat pesanan
                break;          
            case 6:
                return;
            default:
                cout << " Pilihan tidak tersedia\n";
        }
    } while (true);
}



void lihatPesananSayaCustomer(user *currentUser) {
    if (front == nullptr) {
        cout << "Tidak ada pesanan yang tersedia.\n";
        return;
    }

    pesanan *current = front; 
    while (current != nullptr) {
        if (current->userID == currentUser->userID) {
            cout << "------ Detail Pesanan ------\n";
            cout << "Nama : " << current->username << endl;
            cout << "ID   : " << current->userID << endl;
            cout << "Alamat : " << current->alamat << endl;

            keranjang *barang = current->barang;
            int total = 0;
            while (barang != nullptr) {
                cout << "=============================\n";
                cout << "Id : " << barang->idBarang << endl;
                cout << "Nama : " << barang->namaBarang << endl;
                cout << "Harga : " << barang->harga << endl;
                cout << "Quantity : " << barang->quantity << endl;
                total += barang->harga * barang->quantity;
                barang = barang->next;
            }
            
            cout << "=============================\n";
            cout << "Total : " << total << endl;
            cout << "Status : " << current->status << endl;

            if (current->status == "Pesanan Sedang dalam Proses Pengiriman") {
                cout << "Apakah Pesananmu sudah sampai?\n";
                cout << "1. Sudah Dongg\n";
                cout << "2. Belumm :(\n";
                cout << "Pilihan: ";
                int choice;
                cin >> choice;

                if (choice == 1) {
                    riwayatPesanan *newRiwayat = new riwayatPesanan(current->userID, current->username, current->alamat, current->barang, "Pesanan Telah Diterima");
                    newRiwayat->next = riwayatFront;
                    riwayatFront = newRiwayat;

                    
                    if (current->prev != nullptr) {
                        current->prev->next = current->next;
                    } else {
                        front = current->next; 
                    }
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    }

                    cout << "Pesanan telah diterima!\n";
                    pesanan *temp = current;
                    current = current->next;
                    delete temp; 
                } else {
                    cout << "Yang sabar ya bos..\n";
                }
            }
            cout << "Press any key to continue . . . ";
            cin.ignore();
            cin.get();
            return;
        }
    }
}

void lihatRiwayatPesananCustomer(user *currentUser) {
    if (riwayatFront == nullptr) {
        cout << "Tidak ada lagi pesanan yang tersedia.\n";
        return;
    }

    riwayatPesanan *current = riwayatFront;
    bool adaPesanan = false;
    while (current != nullptr) {
        if (current->userID == currentUser->userID && 
            (current->status == "Pesanan Telah Diterima" || current->status == "Pesanan dibatalkan oleh Admin")) {
            adaPesanan = true;
            cout << "------ Riwayat Pembelian ------\n";
            cout << "Nama    : " << current->username << endl;
            cout << "ID      : " << current->userID << endl;
            cout << "Alamat  : " << current->alamat << endl;

            keranjang *barang = current->barang;
            int total = 0;
            while (barang != nullptr) {
                cout << "=============================\n";
                cout << "Id       : " << barang->idBarang << endl;
                cout << "Nama     : " << barang->namaBarang << endl;
                cout << "Harga    : " << barang->harga << endl;
                cout << "Quantity : " << barang->quantity << endl;
                total += barang->harga * barang->quantity;
                barang = barang->next;
            }
            cout << "=============================\n";
            cout << "Total    : " << total << endl;
            cout << "Status   : " << current->status << endl;

            cout << "Press any key to continue . . . ";
            cin.ignore();
            cin.get();
        }
        current = current->next;
    }

    if (!adaPesanan) {
        cout << "Tidak ada lagi pesanan yang tersedia.\n";
    }
}

void insertUser(user *&userlist, string username, string userID, string password, string role) {
        user *newuser = new user(username, password, role, "");
        newuser->userID = userID;
        newuser->next = userlist;
        userlist = newuser;
}

void Register(barang* head, keranjang* cart, pesanan* pesanan) {

    int pilihan;
    string username, tanggallahir, password, role, userID, alamat;
    int peran;

    cout << " ----- Registrasi -----\n";
    cout << " 1. Admin\n";
    cout << " 2. Customer\n";
    cout << " Pilihan: ";
    cin >> pilihan;

    switch (pilihan){
        case 1: {
            cout << " ------ Admin ------\n";
            cout << " Nama: ";
            cin.ignore();
            getline(cin, username);
            cout << " Tanggal Lahir (dd/mm/yyyy): ";
            cin >> tanggallahir;
            cout << " Password: ";
            cin >> password;    
            peran = 0;
            role = "Admin";

            user newUser(username, password, role, tanggallahir);
            createID(newUser, peran);

            userID = newUser.userID;
            cout << " ID: " << userID << endl;

            insertUser(userlist, username, userID, password, role);
            
            ofstream file("pengguna.txt", ios::app);
            if (file.is_open()) {
                file << "ID: "<<userID << endl 
                     << "Username: "<<username << endl 
                     << "Tanggal Lahir: "<<tanggallahir << endl 
                     << "Role: "<<role << endl
                     << "Password: "<<password << endl
                     << "Alamat: "<<alamat << endl;
                file.close();
            } else {
                cout << "Gagal untuk menyimpan data!\n";
            }
            break;
        }
        case 2: {
            cout << " ------ Customer ------\n";
            cout << " Nama: ";
            cin.ignore();
            getline(cin, username);
            cout << " Tanggal Lahir (dd/mm/yyyy): ";
            cin >> tanggallahir;
            cout << " Password: ";
            cin >> password;
            cout << " Alamat: ";
            cin.ignore();
            getline(cin, alamat);
            peran = 1;
            role = "Customer";

            user newUser(username, password, role, tanggallahir, alamat);
            createID(newUser, peran);

            userID = newUser.userID;
            cout << " ID: " << userID<< endl;

            insertUser(userlist, username, userID, password, role);
            ofstream file("pengguna.txt", ios::app);
            if (file.is_open()) {
                file << "ID: "<< userID << endl 
                     << "Username: "<<username << endl 
                     << "Tanggal Lahir: "<<tanggallahir << endl 
                     << "Role: "<<role << endl
                     << "Password: "<<password << endl
                     << "Alamat: "<<alamat << endl;
                file.close();
            } else {
                cout << "Gagal untuk menyimpan data!\n";
            }
            break;
        }
        default:
            cout << " Pilihan tidak tersedia\n";
    }

}

void login(barang* head, keranjang* cart, pesanan* pesanan) {
    string userID, password, storedUserID, storedUsername, storedTanggalLahir, storedRole, storedPassword, storedalamat;
    bool logsuccess = false;
    
    while (!logsuccess) {
        cout << " ------ Login ------\n";
        cout << " ID: ";
        cin >> userID;
        cout << " Password: ";
        cin >> password;
        
        ifstream file("pengguna.txt");
        if (!file.is_open()) {
            cout << "Gagal membuka file pengguna!\n";
            return;
        }
        string line;
        while (getline(file, line)&&!logsuccess) {
            if (line.find("ID: ") == 0) {
                storedUserID = line.substr(4);
                getline(file, line);
                storedUsername = line.substr(10);
                getline(file, line);
                storedTanggalLahir = line.substr(15);
                getline(file, line);
                storedRole = line.substr(6);
                getline(file, line);
                storedPassword = line.substr(10);
                getline(file, line);
                storedalamat = line.substr(8);
                if (storedUserID == userID && storedPassword == password) {
                    logsuccess = true;
                    cout << " Login berhasil! Selamat datang, " << storedUsername<< endl;
                    user *currentUser = new user(storedUsername, storedPassword, storedRole, storedTanggalLahir, storedalamat);
                    currentUser->userID = storedUserID;    
                    if (userID.back() == '0') {
                            cout << " Anda masuk sebagai Admin\n";
                            admin();
                        } else {
                            cout << " Anda masuk sebagai Customer\n";
                            customer(currentUser);
                        }
                        file.close();
                        return;
                }
            }   
        }
        file.close();

        if (!logsuccess) {
            cout << " ID atau Password salah. Apakah Anda ingin mendaftar? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                Register(head, cart, pesanan);
                return;
            } else {
                cout << " Silakan coba login lagi\n";
            }   
        }
    }
}

void keluar(){
    cout << " ------ Keluar ------\n"
         << " ===========================================\n"
         << "\n"
         << " Terima kasih telah menggunakan aplikasi ini\n"
         << "\n"
         << " ===========================================\n";
}

void pilih(barang* head, keranjang* cart, pesanan* pesanan) {
    int pilihan;
    do {
        cout << " ------ Selamat Datang ------\n"
             << " 1. Registrasi\n"
             << " 2. Login\n"
             << " 3. Keluar\n"
             << " Pilihan: ";
        cin >> pilihan;

        switch (pilihan){
            case 1:
                Register(head, cart, pesanan);
                break;
            case 2:
                login(head, cart, pesanan);
                break;
            case 3:
                keluar();
                break;
            default:
                cout << " Pilihan tidak tersedia" << endl;
        }
    } while (pilihan != 3);
}

int main() {
    barang* head = nullptr;                    
    keranjang* cart = nullptr;                 
    pesanan* pesanan = nullptr;                
    userlist = nullptr;                        
    front = nullptr;                           
    rear = nullptr;                            
    riwayatFront = nullptr;
      
    pilih(head, cart, pesanan); 
    return 0;                                 
}
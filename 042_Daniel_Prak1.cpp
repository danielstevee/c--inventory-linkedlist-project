#include <iostream>
#include <fstream>
using namespace std;

struct User{
    string username;
    string password;
    string role;
    string tanggalLahir;
    string id;
    User() {}
    User(string username, string password, string tanggalLahir, string role){
        this->username = username;
        this->password = password;
        this->role = role;
        this->tanggalLahir = tanggalLahir;
        id = makeID();
    }
    
    string makeID(){
        string tempID;
        // Digit 1 - 2
        char dummy = toupper(username.front());
        tempID = to_string(((int)dummy - 'A' + 1) % 10);
        dummy = toupper(username.back());
        tempID += to_string(((int)dummy - 'A' + 1) % 10);
        
        // Digit 3
        int index = 0;
        string temp2 = "";
        int total = 0; 
        for (char ch : tanggalLahir) {
            if (ch == '-' ) {// semacam melompati garis pemisah
                if (!temp2.empty()) {
                    total += stoi(temp2);
                    temp2 = "";//mengosongkan
                }
            } else {
                temp2 += ch; 
            }
            if (index == tanggalLahir.length() - 1 && !temp2.empty()) {
                total += stoi(temp2);
            }
            index++; 
        }
        tempID += to_string(total % 10);
        
        // Digits 4 - 5
        index = 0;
        int counter = 0; 
        for (char ch : password) {
            if (counter == 2) {
                break;
            } else if (ch >= '0' && ch <= '9') {
                tempID += ch;
                counter++;
            }
            index++;
        }
        if (index == password.length() && counter == 1) {
            tempID += '0';
        }
        
        // Digit 6
        if (role == "admin") {
            tempID += "0";
        } else if (role == "customer") {
            tempID += "1";
        }
        
        return tempID;
    }
};

const int MAX_USERS = 100;  
User users[MAX_USERS];      
int userCount = 0;          

void MenuUtama();
void MenuRegistrasi();
void registrasiAdmin();
void registrasiCustomer();
void login();
bool isValidName(const string& name);
bool isValidPassword(const string& password);
bool isValidTanggalLahir(const string& tanggalLahir);
User* cariUserById(const string& id);
void adminMenu();
void customerMenu();
void tambahBarang();
void daftarBarangAdmin();
void daftarBarangCustomer();
void cariBarang();
int main() {
    int pilihan;
    while (true) {
        MenuUtama();
        cin >> pilihan;

        if (pilihan == 1) {
            int regPilihan;
            MenuRegistrasi();
            cin >> regPilihan;

            if (regPilihan == 1) {
                cout << "Registrasi sebagai Admin" << endl;
                registrasiAdmin();
            } else if (regPilihan == 2) {
                cout << "Registrasi sebagai Customer" << endl;
                registrasiCustomer();
            } else {
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            }
        } else if (pilihan == 2) {
            cout << "------Login------" << endl;
            login();
        } else if (pilihan == 3) {
            cout << "Program berakhir." << endl;
            break;
        } else {
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    }
    return 0;
}

void MenuUtama() {
    cout << "------Selamat Datang!------" << endl;
    cout << "Pilih Menu :" << endl;
    cout << "1. Registrasi" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilihan: " << endl;
}

void MenuRegistrasi() {
    cout << "------Registrasi------" << endl;
    cout << "Anda ingin mendaftar sebagai?" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    cout << "Pilihan: "<< endl;
}

void registrasiAdmin() {

    string nama, password, tanggalLahir;
    cout << "------Registrasi------" << endl;
    cout << "Masukkan Nama: ";
    cin.ignore(); //untuk mengabaikan enter
    getline(cin, nama);
    
    while (!isValidName(nama)) {
        cout << "Nama hanya diperbolehkan menggunakan huruf saja. Masukkan Nama lagi: ";
        getline(cin, nama);
    }

    cout << "Masukkan Tanggal Lahir: ";
    getline(cin, tanggalLahir);

    while (!isValidTanggalLahir(tanggalLahir)) {
        cout << "Tanggal Lahir harus dalam format DD-MM-YYYY dan hanya berisi angka. Masukkan Tanggal Lahir lagi: ";
        getline(cin, tanggalLahir);
    }

    cout << "Masukkan Password: ";
    getline(cin, password);

    while (!isValidPassword(password)) {
        cout << "Password harus berisi kombinasi antara Angka dan Huruf. Masukkan Password lagi: ";
        getline(cin, password);
    }

    User admin(nama, password, tanggalLahir, "admin");
    users[userCount++] = admin;
    cout << "Registrasi sebagai Admin berhasil!" << endl;
    cout << "ID Admin: " << admin.id << endl;
}

void registrasiCustomer() {

    string nama, password, tanggalLahir;
    cout << "------Registrasi------" << endl;
    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, nama);

    while (!isValidName(nama)) {
        cout << "Nama hanya diperbolehkan menggunakan huruf saja. Masukkan Nama lagi: ";
        getline(cin, nama);
    }

    cout << "Masukkan Tanggal Lahir: ";
    getline(cin, tanggalLahir);

    while (!isValidTanggalLahir(tanggalLahir)) {
        cout << "Tanggal Lahir harus dalam format DD-MM-YYYY dan hanya berisi angka. Masukkan Tanggal Lahir lagi: ";
        getline(cin, tanggalLahir);
    }

    cout << "Masukkan Password: ";
    getline(cin, password);

    while (!isValidPassword(password)) {
        cout << "Password harus berisi kombinasi antara Angka dan Huruf. Masukkan Password lagi: ";
        getline(cin, password);
    }

    User customer(nama, password, tanggalLahir, "customer");
    users[userCount++] = customer;
    cout << "Registrasi sebagai Customer berhasil!" << endl;
    cout << "ID: " << customer.id << endl;
}

void login() {
    string id, password;
    cout << "Masukkan ID: ";
    cin.ignore();
    getline(cin, id);
    cout << "Masukkan Password: ";
    getline(cin, password);

    User* user = cariUserById(id);
    if (user != nullptr && user->password == password) {
        cout << "Login berhasil!" << endl;
        cout << "Selamat datang, " << user->username << "!" << endl;
        if (user->role == "admin") {
            adminMenu();
        } else if (user->role == "customer") {
            customerMenu();
        }
    } else {
        cout << "ID atau Password salah!" << endl;
        cout << "Belum memiliki akun? Registrasi terlebih dahulu (y/n): ";
        char pilihan;
        cin >> pilihan;
        if (pilihan == 'y' || pilihan == 'Y') {
            MenuRegistrasi();
        } else if (pilihan == 'n' || pilihan == 'N') {
            MenuUtama();
        }
    }
}


void adminMenu() {
    int pilihan;
    while (true) {
        cout << "------Anda Login Sebagai Admin!------" << endl;
        cout << "Pilih Menu :" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Daftar Barang" << endl;
        cout << "3. Logout" << endl;
        cout << "Pilihan: "<<endl;
        cin >> pilihan;

        if (pilihan == 1) {
            tambahBarang();
            cout << "Tambah Barang" << endl;
        } else if (pilihan == 2) {
            daftarBarangAdmin();
            cout << "Daftar Barang" << endl;
        } else if (pilihan == 3) {
            cout << "Logout" << endl;
            MenuUtama();
            break;
        } else {
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            
        }
    }
}

struct Barang {
    string id;
    string nama;
    double harga;
    int stok;
    Barang* next;
};

Barang* head = nullptr;

void tambahBarang() {
    Barang* newBarang = new Barang();

    cout << "------Tambah Barang------" << endl;
    cout << "Masukkan Id: ";
    cin >> newBarang->id;
    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, newBarang->nama);
    cout << "Harga Barang: ";
    cin >> newBarang->harga;
    cout << "Stok Barang: ";
    cin >> newBarang->stok;

    newBarang->next = head;
    head = newBarang;

    char pilihan;
    cout << "Apa Anda ingin menambahkan barang lain? (y/n): ";
    cin >> pilihan;
    if (pilihan == 'y' || pilihan == 'Y') {
        tambahBarang();
    }else if (pilihan == 'n' || pilihan == 'N') {
        adminMenu();
    }
}

void daftarBarangAdmin() {
    if (head == nullptr) {
        cout << "------Daftar Barang------" << endl;
        cout << "Belum ada barang yang tersedia" << endl;
        char pilihan;
        cout << "Apa Anda ingin menambahkan barang? (y/n): ";
        cin >> pilihan;
        if (pilihan == 'y' || pilihan == 'Y') {
            tambahBarang();
        }else if (pilihan == 'n' || pilihan == 'N') {
            adminMenu();
        }
    } else {
        Barang* current = head;
        cout << "------Daftar Barang------" << endl;
        while (current != nullptr) {
            cout << "=============================" << endl;
            cout << "Id : " << current->id << endl;
            cout << "Nama : " << current->nama << endl;
            cout << "Harga : " << current->harga << endl;
            cout << "Stok : " << current->stok << endl;
            current = current->next;
        }
        cout << "=============================" << endl;
    }
}

void customerMenu() {
    int pilihan;
    while (true) {
        cout << "------Anda Login Sebagai Customer!------" << endl;
        cout << "Pilih Menu :" << endl;
        cout << "1. Daftar Barang" << endl;
        cout << "2. Mencari Barang" << endl;
        cout << "3. Logout" << endl;
        cout << "Pilihan: " << endl;
        cin >> pilihan;

        if (pilihan == 1) {
            daftarBarangCustomer();
        } else if (pilihan == 2) {
            cariBarang();
        } else if (pilihan == 3) {
            cout << "Logout" << endl;
            MenuUtama();
            break;
        } else {
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    }
}

void daftarBarangCustomer() {
    if (head == nullptr) {
        cout << "------Daftar Barang------" << endl;
        cout << "Belum ada barang yang tersedia" << endl;
    } else {
        Barang* current = head;
        cout << "------Daftar Barang------" << endl;
        while (current != nullptr) {
            cout << "=============================" << endl;
            cout << "Id : " << current->id << endl;
            cout << "Nama : " << current->nama << endl;
            cout << "Harga : " << current->harga << endl;
            cout << "Stok : " << current->stok << endl;
            current = current->next;
        }
        cout << "=============================" << endl;
    }
}

void cariBarang() {
    if (head == nullptr) {
        cout << "------Cari Barang------" << endl;
        cout << "Belum ada barang yang tersedia" << endl;
    } else {
        string idCari;
        cout << "------Cari Barang------" << endl;
        cout << "Masukkan ID Barang: ";
        cin.ignore();
        getline(cin, idCari);

        Barang* current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->id == idCari) {
                cout << "=============================" << endl;
                cout << "Id : " << current->id << endl;
                cout << "Nama : " << current->nama << endl;
                cout << "Harga : " << current->harga << endl;
                cout << "Stok : " << current->stok << endl;
                found = true;
                break;
            } 
            
        }
        if (!found) {
            cout << "Barang dengan ID \"" << idCari << "\" tidak ditemukan!" << endl;
            customerMenu();
        }
    }
}




User* cariUserById(const string& id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) {
            return &users[i];
        }
    }
    return nullptr;
}

bool isValidName(const string& name) {
    for (int i = 0; i < name.length(); i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) {
            return false;
        }
    }
    return true;
}

bool isValidPassword(const string& password) {
    bool hasLetter = false;
    bool hasDigit = false;

    for (int i = 0; i < password.length(); i++) {
        if ((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z')) {
            hasLetter = true;
        }
        if (password[i] >= '0' && password[i] <= '9') {
            hasDigit = true;
        }
    }

    return hasLetter && hasDigit;
}

bool isValidTanggalLahir(const string& tanggalLahir) {
    if (tanggalLahir.length() != 10) {
    }
    for (int i = 0; i < tanggalLahir.length(); i++) {
        if (i == 2 || i == 5) {
            if (tanggalLahir[i] != '-') {
                return false;
            }
        } else {
            if (tanggalLahir[i] < '0' || tanggalLahir[i] > '9') {//cek ada angka atau tidak
                return false;
            }
        }
    }
    return true;
}

# 🛒 C++ Inventory & E-Commerce Management System (Linked List Version)

Sistem manajemen toko berbasis **C++ Console Application** yang sudah ditingkatkan menjadi sistem **e-commerce sederhana**, lengkap dengan fitur:

- Registrasi & Login user (Admin & Customer)
- Manajemen barang (CRUD sederhana + navigasi)
- Sistem keranjang belanja
- Sistem checkout & pesanan
- Riwayat pesanan
- Penyimpanan data ke file (`pengguna.txt`)
- Struktur data Linked List (Single, Double, Queue)

---

## 🚀 Features

### 👤 User System
- Registrasi Admin & Customer
- Login menggunakan ID & Password
- Auto Generate User ID
- Penyimpanan data user ke file
- Role-based access (Admin / Customer)

---

### 📦 Inventory System
- Tambah Barang (Admin)
- Daftar Barang (Double Linked List navigation)
- Cari Barang (by ID / Nama)
- Stock management saat checkout

---

### 🛒 Shopping System
- Keranjang belanja (Linked List)
- Tambah barang ke keranjang
- Checkout sistem
- Nota pembelian otomatis

---

### 📑 Order System
- Queue pesanan (FIFO)
- Admin bisa:
  - Lihat & approve pesanan
  - Tolak pesanan
  - Update status pesanan

---

### 📜 History System
- Riwayat pesanan user
- Status:
  - Menunggu Pembayaran
  - Sedang Diproses
  - Diterima
  - Ditolak

---

## 🧠 Data Structures Used

- Singly Linked List → Keranjang
- Doubly Linked List → Barang & Riwayat
- Queue → Pesanan
- File Handling (`fstream`)
- Dynamic Memory Allocation

---

## 🔐 User ID System

User ID dibuat otomatis berdasarkan:
- Huruf depan & belakang username
- Tanggal lahir
- Password (angka tertentu)
- Role (Admin / Customer)

Contoh:
```
Username : Daniel
Password : dan123
Tanggal  : 12-05-2005
Role     : Admin

Generated ID : 451230
```

---

## 🏗️ Program Flow

```
Main Menu
│
├── Registrasi
│   ├── Admin
│   └── Customer
│
├── Login
│   ├── Admin Menu
│   │   ├── Tambah Barang
│   │   ├── Lihat Barang
│   │   ├── Pesanan
│   │   └── Riwayat
│
│   └── Customer Menu
│       ├── Lihat Barang
│       ├── Cari Barang
│       ├── Keranjang
│       ├── Checkout
│       ├── Pesanan Saya
│       └── Riwayat
│
└── Exit
```

---

## ⚙️ Technologies

- C++
- STL (fstream, iostream, ctime)
- Linked List (Single & Double)
- Queue System
- File Storage System

---

## 💾 Data Storage

User data disimpan di:
```
pengguna.txt
```

Format:
```
ID
Username
Tanggal Lahir
Role
Password
Alamat
```

---

## 🚀 How to Run

### Compile
```bash
g++ main.cpp -o app
```

### Run (Windows)
```bash
app.exe
```

---

## 📸 Preview

```
------ Selamat Datang ------
1. Registrasi
2. Login
3. Keluar
```

---

## 📚 Learning Outcome

Project ini dibuat untuk memahami:
- Linked List (Single & Double)
- Queue (FIFO system)
- File handling C++
- Sistem login & registrasi
- Simulasi e-commerce sederhana
- Manajemen memory (dynamic allocation)

---

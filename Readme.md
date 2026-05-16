# 🛒 C++ E-Commerce System (Linked List Based)

Sistem mini e-commerce berbasis **C++ Console Application** yang dibuat menggunakan struktur data **Linked List, Queue, dan Doubly Linked List** untuk mensimulasikan sistem toko online sederhana.

## ✨ Features

### 👤 Authentication System
- Registrasi Admin & Customer
- Login menggunakan ID & Password
- Auto Generate User ID berdasarkan:
  - Username
  - Tanggal lahir
  - Password
  - Role
- Data user disimpan ke file `pengguna.txt`

### 📦 Inventory Management (Admin)
- Tambah barang
- Lihat daftar barang
- Struktur data: Doubly Linked List

### 🛒 Shopping System (Customer)
- Lihat daftar barang
- Cari barang berdasarkan ID / nama
- Tambah barang ke keranjang (cart)

### 🧺 Cart System
- Menyimpan barang sebelum checkout
- Hitung total belanja
- Hapus item otomatis saat checkout

### 📦 Order System (Queue)
- Checkout barang dari keranjang
- Sistem antrian pesanan (FIFO Queue)
- Admin bisa approve atau reject pesanan

### 🚚 Order Status
- Menunggu pembayaran
- Diproses / Pengiriman
- Diterima customer
- Ditolak admin

### 📜 Riwayat Pesanan
- Menyimpan histori transaksi
- Bisa diakses Admin & Customer
- Status final: diterima atau ditolak

## 🧠 Data Structure Used
- Struct
- Singly Linked List
- Doubly Linked List
- Queue (FIFO)
- Pointer
- File Handling (fstream)

## 🔐 User ID Generator
User ID dibuat otomatis dari:
- Huruf awal & akhir username
- Tanggal lahir
- Digit password
- Role (Admin / Customer)

## 🏗️ Program Flow
Main Menu
│
├── Registrasi
├── Login
│
├── Admin Menu
│ ├── Tambah Barang
│ ├── Lihat Barang
│ ├── Kelola Pesanan (Approve / Reject)
│ └── Riwayat Pesanan
│
├── Customer Menu
│ ├── Lihat Barang
│ ├── Cari Barang
│ ├── Keranjang
│ ├── Checkout
│ ├── Pesanan Saya
│ └── Riwayat Pesanan
│
└── Exit

## ⚙️ Technologies
- C++
- g++ Compiler
- Visual Studio Code

## 🚀 How to Run

### Compile
```bash
g++ main.cpp -o app
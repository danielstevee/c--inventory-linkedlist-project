# 🛒 C++ Inventory Management System

Sistem manajemen barang sederhana berbasis **C++ Console Application** dengan fitur registrasi user, login authentication, role admin/customer, dan pengelolaan barang menggunakan **Linked List**.

---

## ✨ Features

### 👤 Authentication System
- Registrasi Admin & Customer
- Login menggunakan ID dan Password
- Auto Generate User ID
- Validasi:
  - Nama
  - Password
  - Tanggal Lahir

### 📦 Inventory Management

#### Admin
- Tambah Barang
- Lihat Daftar Barang

#### Customer
- Lihat Daftar Barang
- Cari Barang berdasarkan ID

---

## 🧠 Data Structure Used

- `Struct`
- `Array`
- `Linked List`
- `Pointer`

---

## 🔐 User ID Generator

ID user dibuat otomatis berdasarkan:
- Huruf awal username
- Huruf akhir username
- Total digit tanggal lahir
- Angka pada password
- Role user

Contoh:

```txt
Username : Steven
Tanggal  : 12-05-2005
Password : dan123
Role     : admin

Generated ID : 451230
```

---

## 🏗️ Program Structure

```txt
Main Menu
│
├── Registrasi
│   ├── Admin
│   └── Customer
│
├── Login
│   ├── Admin Menu
│   │   ├── Tambah Barang
│   │   └── Daftar Barang
│   │
│   └── Customer Menu
│       ├── Daftar Barang
│       └── Cari Barang
│
└── Exit
```

---

## ⚙️ Technologies

- Language : C++
- IDE : Visual Studio Code
- Compiler : g++

---

## 🚀 How to Run

### Compile

```bash
g++ main.cpp -o app
```

### Run

Linux / Mac:
```bash
./app
```

Windows:
```bash
app.exe
```

---

## 📸 Preview

```txt
------Selamat Datang!------
1. Registrasi
2. Login
3. Keluar
```

---

## 📚 Learning Purpose

Project ini dibuat untuk mempelajari:
- Dasar C++
- Struct & Pointer
- Linked List
- Authentication System
- CRUD sederhana
- Validasi Input

---
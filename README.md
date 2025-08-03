
# 🛒 Inventory Management System (C++)

This is a simple inventory management system written in **C++**, using recursive functions, static arrays, and file handling to simulate a CLI-based stock system for a small shop.

## ✨ Features

- ✅ Add new items to inventory (recursive input)
- 📋 Display all stored items from file
- 💸 Sell items (automatically reduce stock and calculate total)
- 🗑️ Delete items (with automatic backup to `backupdata.txt`)
- ♻️ Restore items from backup file
- 📁 Save and read data using external text files (`inventory.txt` & `backupdata.txt`)

## 🧠 Concepts Used

- `struct` for item data
- Static array of max 100 items
- Recursive function for repeated input
- File I/O: `ofstream` and `ifstream`

## 🚀 How to Run

Compile and run using a C++ compiler:

```bash
g++ -o inventory inventory.cpp
./inventory
```

Follow the interactive menu to manage your shop's inventory.

## 📂 File Overview

- `inventory.txt` → Stores active inventory items
- `backupdata.txt` → Stores deleted items for restoration

## 📌 Notes

- Maximum capacity: 100 items
- CLI-based interface
- Good for learning recursion, file handling, and struct array management

---

> Created by **Daniel Steven Setyawan**  
> Informatics Engineering Student | UI/UX • Frontend • C++ • Cyber Security  

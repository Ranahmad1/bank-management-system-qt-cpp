# 🏦 Bank Management System — Qt 6 / C++17

<div align="center">

> A fully-featured desktop banking application built with **Qt 6** and **C++17** — by **[Rana Ahmad](https://github.com/Ranahmad1)**

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt_6-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-3B82F6?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

**A production-style desktop banking application with persistent storage, CNIC validation, and a clean dark UI.**

</div>

---

## ✨ Features

- 👤 **Customer Management** — Register customers with Pakistan CNIC validation; support multiple accounts per customer
- 🏦 **Account Types** — Savings (minimum balance enforced), Current, and Fixed Deposit accounts
- 💳 **Transactions** — Deposit, withdrawal, and inter-account transfers with full transaction history
- 📊 **Live Dashboard** — Real-time stats: total customers, accounts, balances, and active accounts
- 💾 **Persistent Storage** — JSON-based local storage via `QJsonDocument` — no external database required
- 🎨 **Dark UI** — Clean dark-themed interface built with Qt Fusion style

---

## 📁 Project Structure

```
bank-management-system-qt-cpp/
├── BankManagementSystem.pro   # Qt project file
├── src/
│   ├── main.cpp               # App entry point, dark theme setup
│   ├── loginwindow.cpp        # Login UI with shadow card
│   ├── mainwindow.cpp         # Main window + sidebar navigation
│   ├── dashboard.cpp          # Live stats dashboard
│   ├── account.cpp            # Account logic (deposit, withdraw, transfer)
│   ├── customer.cpp           # Customer model + CNIC validation
│   ├── transaction.cpp        # Transaction formatting
│   └── database.cpp           # JSON persistence layer
├── include/                   # Header files (matching each .cpp)
├── docs/
│   └── SETUP.md               # Full build & run instructions
└── .github/workflows/         # CI checks
```

---

## 🚀 Quick Start

See [docs/SETUP.md](docs/SETUP.md) for full platform-specific build instructions.

```bash
git clone https://github.com/Ranahmad1/bank-management-system-qt-cpp.git
cd bank-management-system-qt-cpp

# Option A: Qt Creator (recommended)
# Open BankManagementSystem.pro → Press Ctrl+R

# Option B: Command line
qmake BankManagementSystem.pro
make -j$(nproc)
./BankManagementSystem
```

**Default login credentials:** `admin` / `admin123`

---

## 🛠 Tech Stack

| Component | Technology |
|---|---|
| **Language** | C++17 |
| **GUI Framework** | Qt 6 (Widgets, Core, GUI) |
| **Persistence** | JSON via QJsonDocument |
| **Build System** | qmake |
| **Platform** | Windows, Linux, macOS |

---

## 📋 Prerequisites

- Qt 6.2+ with Qt Creator
- C++17-compatible compiler (GCC 10+, MSVC 2019+, Clang 12+)
- CMake or qmake

---

## 👤 Author

**Rana Ahmad** — Full Stack Engineer & C++ Developer

- 🌐 [Portfolio](https://ranahmad1.github.io/rana-ahmad-portfolio/)
- 💼 [LinkedIn](https://www.linkedin.com/in/rana-ahmad-896004365/)
- 🐙 [GitHub](https://github.com/Ranahmad1)
- 📧 ahmadaslam0904@gmail.com
- 📍 Faisalabad, Pakistan

Full Stack Engineer @ MADigital.pk | Building FlexERP | BSCS @ University of Central Punjab

---

## 📄 License

MIT License — free to use, modify, and distribute. See [LICENSE](LICENSE) for details.

---

*Keywords: bank management system C++ · Qt 6 desktop app · C++17 Qt project · banking application Qt · C++ GUI application · Qt Creator project · desktop banking software · Pakistan CNIC validation C++ · Rana Ahmad C++ project · open source Qt banking*

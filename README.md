# Bank Management System — Qt/C++

<div align="center">

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt_6-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-3B82F6?style=for-the-badge)

**A desktop banking application built with Qt 6 and C++17.**

</div>

---

## Features

- 👤 **Customer Management** — Register customers with CNIC validation (Pakistan format), manage multiple accounts per customer
- 🏦 **Account Types** — Savings (min balance enforced), Current, and Fixed Deposit accounts
- 💳 **Transactions** — Deposit, withdrawal, and inter-account transfers with full transaction history
- 📊 **Dashboard** — Live stats: total customers, accounts, balances, and active accounts
- 💾 **Persistent Storage** — JSON-based local storage, no external DB required
- 🎨 **Dark UI** — Clean dark-themed interface with Qt Fusion style

## Project Structure

```
bank-management-system-qt-cpp/
├── BankManagementSystem.pro   # Qt project file
├── src/
│   ├── main.cpp               # App entry point, dark theme setup
│   ├── loginwindow.cpp        # Login UI with shadow card
│   ├── mainwindow.cpp         # Main window + sidebar navigation
│   ├── dashboard.cpp          # Live stats dashboard
│   ├── account.cpp            # Account logic (deposit/withdraw/transfer)
│   ├── customer.cpp           # Customer model + CNIC validation
│   ├── transaction.cpp        # Transaction formatting
│   └── database.cpp           # JSON persistence layer
├── include/                   # Header files
├── docs/
│   └── SETUP.md               # Build & run instructions
└── .github/workflows/         # CI checks
```

## Quick Start

See [docs/SETUP.md](docs/SETUP.md) for full build instructions.

```bash
git clone https://github.com/Ranahmad1/bank-management-system-qt-cpp.git
cd bank-management-system-qt-cpp
# Open BankManagementSystem.pro in Qt Creator and press Ctrl+R
```

**Default login:** `admin` / `admin123`

## Tech Stack

- **Language:** C++17
- **Framework:** Qt 6 (Widgets, Core, GUI)
- **Storage:** JSON (QJsonDocument)
- **Build:** qmake

## Author

**Rana Ahmad** — Full Stack Engineer at MADigital.pk  
[LinkedIn](https://linkedin.com/in/ranahmad0) · [Portfolio](https://ranahmad1.github.io/rana-ahmad-portfolio/)

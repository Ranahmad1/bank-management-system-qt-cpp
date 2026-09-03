# Setup Guide

## Prerequisites

- Qt 6.x (or Qt 5.15+)
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Qt Creator (recommended) or any IDE

## Build Instructions

### Using Qt Creator (Recommended)

1. Open `BankManagementSystem.pro` in Qt Creator
2. Configure the kit (Qt version + compiler)
3. Press **Ctrl+R** to build and run

### Using Command Line

```bash
# Clone the repository
git clone https://github.com/Ranahmad1/bank-management-system-qt-cpp.git
cd bank-management-system-qt-cpp

# Build
mkdir build && cd build
qmake ../BankManagementSystem.pro
make -j$(nproc)

# Run
./BankManagementSystem
```

## Default Login

| Field    | Value      |
|----------|------------|
| Username | `admin`    |
| Password | `admin123` |

## Features

- Customer registration with CNIC validation (Pakistan format)
- Multiple account types: Savings, Current, Fixed Deposit
- Deposit, withdrawal, and inter-account transfer
- Full transaction history per account
- JSON-based persistent storage
- Dark-themed modern UI
- Dashboard with live stats

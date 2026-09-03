#include "../include/account.h"
#include <QDateTime>
#include <QUuid>
#include <stdexcept>

Account::Account(const QString &accountNumber, const QString &ownerName,
                 AccountType type, double initialBalance)
    : m_accountNumber(accountNumber)
    , m_ownerName(ownerName)
    , m_type(type)
    , m_balance(initialBalance)
    , m_isActive(true)
    , m_createdAt(QDateTime::currentDateTime())
{
    if (initialBalance < 0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }
}

bool Account::deposit(double amount, const QString &description)
{
    if (amount <= 0) return false;
    if (!m_isActive) return false;

    m_balance += amount;

    Transaction txn;
    txn.id = QUuid::createUuid().toString(QUuid::WithoutBraces).left(8).toUpper();
    txn.type = Transaction::Deposit;
    txn.amount = amount;
    txn.balanceAfter = m_balance;
    txn.description = description.isEmpty() ? "Deposit" : description;
    txn.timestamp = QDateTime::currentDateTime();
    m_transactions.append(txn);

    return true;
}

bool Account::withdraw(double amount, const QString &description)
{
    if (amount <= 0) return false;
    if (!m_isActive) return false;
    if (m_balance < amount) return false;  // Insufficient funds

    // Savings accounts: minimum balance check
    if (m_type == Savings && (m_balance - amount) < SAVINGS_MIN_BALANCE) {
        return false;
    }

    m_balance -= amount;

    Transaction txn;
    txn.id = QUuid::createUuid().toString(QUuid::WithoutBraces).left(8).toUpper();
    txn.type = Transaction::Withdrawal;
    txn.amount = amount;
    txn.balanceAfter = m_balance;
    txn.description = description.isEmpty() ? "Withdrawal" : description;
    txn.timestamp = QDateTime::currentDateTime();
    m_transactions.append(txn);

    return true;
}

bool Account::transfer(Account &target, double amount)
{
    if (!withdraw(amount, "Transfer to " + target.accountNumber())) return false;
    target.deposit(amount, "Transfer from " + m_accountNumber);
    return true;
}

QString Account::accountTypeString() const
{
    switch (m_type) {
        case Savings:  return "Savings";
        case Current:  return "Current";
        case Fixed:    return "Fixed Deposit";
        default:       return "Unknown";
    }
}

QList<Transaction> Account::recentTransactions(int count) const
{
    int start = qMax(0, m_transactions.size() - count);
    return m_transactions.mid(start);
}

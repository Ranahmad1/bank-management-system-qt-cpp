#pragma once
#include <QString>
#include <QList>
#include <QDateTime>

struct Transaction {
    enum Type { Deposit, Withdrawal, Transfer };
    QString   id;
    Type      type;
    double    amount;
    double    balanceAfter;
    QString   description;
    QDateTime timestamp;
};

class Account
{
public:
    enum AccountType { Savings, Current, Fixed };

    static constexpr double SAVINGS_MIN_BALANCE = 500.0;

    Account(const QString &accountNumber, const QString &ownerName,
            AccountType type, double initialBalance = 0.0);

    // Core operations
    bool deposit(double amount, const QString &description = {});
    bool withdraw(double amount, const QString &description = {});
    bool transfer(Account &target, double amount);

    // Getters
    QString     accountNumber() const { return m_accountNumber; }
    QString     ownerName()     const { return m_ownerName; }
    AccountType accountType()   const { return m_type; }
    double      balance()       const { return m_balance; }
    bool        isActive()      const { return m_isActive; }
    QDateTime   createdAt()     const { return m_createdAt; }
    QString     accountTypeString() const;

    const QList<Transaction>& transactions() const { return m_transactions; }
    QList<Transaction> recentTransactions(int count = 10) const;

    // Setters
    void setActive(bool active) { m_isActive = active; }

    // Restore persisted state when loading from disk (does not touch the balance)
    void restoreState(const QDateTime &createdAt, bool active,
                      const QList<Transaction> &transactions);

private:
    QString          m_accountNumber;
    QString          m_ownerName;
    AccountType      m_type;
    double           m_balance;
    bool             m_isActive;
    QDateTime        m_createdAt;
    QList<Transaction> m_transactions;
};

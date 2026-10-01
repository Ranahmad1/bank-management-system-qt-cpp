#pragma once
#include "account.h"
#include <QString>
#include <QList>
#include <QDateTime>
#include <QSharedPointer>

class Customer
{
public:
    Customer(const QString &name, const QString &cnic,
             const QString &phone, const QString &email,
             const QString &address);

    bool addAccount(QSharedPointer<Account> account);
    bool removeAccount(const QString &accountNumber);
    QSharedPointer<Account> findAccount(const QString &accountNumber) const;
    double totalBalance() const;
    bool   isValidCNIC() const;

    // Getters
    QString   customerId()   const { return m_customerId; }
    QString   name()         const { return m_name; }
    QString   cnic()         const { return m_cnic; }
    QString   phone()        const { return m_phone; }
    QString   email()        const { return m_email; }
    QString   address()      const { return m_address; }
    QDateTime registeredAt() const { return m_registeredAt; }
    const QList<QSharedPointer<Account>>& accounts() const { return m_accounts; }

    // Restore persisted identity when loading from disk
    void restoreIdentity(const QString &id, const QDateTime &registeredAt);

    // Setters
    void setName(const QString &n)    { m_name = n; }
    void setPhone(const QString &p)   { m_phone = p; }
    void setEmail(const QString &e)   { m_email = e; }
    void setAddress(const QString &a) { m_address = a; }

private:
    QString   m_customerId;
    QString   m_name;
    QString   m_cnic;
    QString   m_phone;
    QString   m_email;
    QString   m_address;
    QDateTime m_registeredAt;
    QList<QSharedPointer<Account>> m_accounts;
};

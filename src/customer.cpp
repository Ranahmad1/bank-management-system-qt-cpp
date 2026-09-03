#include "../include/customer.h"
#include <QUuid>

Customer::Customer(const QString &name, const QString &cnic,
                   const QString &phone, const QString &email,
                   const QString &address)
    : m_customerId(QUuid::createUuid().toString(QUuid::WithoutBraces).left(8).toUpper())
    , m_name(name)
    , m_cnic(cnic)
    , m_phone(phone)
    , m_email(email)
    , m_address(address)
    , m_registeredAt(QDateTime::currentDateTime())
{
}

bool Customer::addAccount(QSharedPointer<Account> account)
{
    if (!account) return false;
    m_accounts.append(account);
    return true;
}

bool Customer::removeAccount(const QString &accountNumber)
{
    for (int i = 0; i < m_accounts.size(); ++i) {
        if (m_accounts[i]->accountNumber() == accountNumber) {
            m_accounts.removeAt(i);
            return true;
        }
    }
    return false;
}

QSharedPointer<Account> Customer::findAccount(const QString &accountNumber) const
{
    for (const auto &acc : m_accounts) {
        if (acc->accountNumber() == accountNumber)
            return acc;
    }
    return nullptr;
}

double Customer::totalBalance() const
{
    double total = 0.0;
    for (const auto &acc : m_accounts)
        total += acc->balance();
    return total;
}

bool Customer::isValidCNIC() const
{
    // Pakistan CNIC format: 00000-0000000-0 (13 digits)
    QString digits = m_cnic;
    digits.remove('-');
    return digits.length() == 13 && digits.toULongLong() > 0;
}

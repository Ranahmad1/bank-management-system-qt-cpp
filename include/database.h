#pragma once
#include "customer.h"
#include <QList>
#include <QSharedPointer>

class Database
{
public:
    static Database& instance(); // Singleton

    bool saveCustomers(const QList<QSharedPointer<Customer>> &customers);
    QList<QSharedPointer<Customer>> loadCustomers();

private:
    Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    QString m_dataPath;
};

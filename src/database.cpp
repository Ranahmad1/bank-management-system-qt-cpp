#include "../include/database.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QStandardPaths>

Database& Database::instance()
{
    static Database db;
    return db;
}

Database::Database()
    : m_dataPath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/data")
{
    QDir().mkpath(m_dataPath);
}

bool Database::saveCustomers(const QList<QSharedPointer<Customer>> &customers)
{
    QJsonArray array;
    for (const auto &c : customers) {
        QJsonObject obj;
        obj["id"]      = c->customerId();
        obj["name"]    = c->name();
        obj["cnic"]    = c->cnic();
        obj["phone"]   = c->phone();
        obj["email"]   = c->email();
        obj["address"] = c->address();
        obj["registered"] = c->registeredAt().toString(Qt::ISODate);

        QJsonArray accounts;
        for (const auto &acc : c->accounts()) {
            QJsonObject aObj;
            aObj["number"]  = acc->accountNumber();
            aObj["type"]    = acc->accountTypeString();
            aObj["balance"] = acc->balance();
            aObj["active"]  = acc->isActive();
            aObj["created"] = acc->createdAt().toString(Qt::ISODate);

            QJsonArray txns;
            for (const auto &t : acc->transactions()) {
                QJsonObject tObj;
                tObj["id"]          = t.id;
                tObj["type"]        = (int)t.type;
                tObj["amount"]      = t.amount;
                tObj["balance"]     = t.balanceAfter;
                tObj["description"] = t.description;
                tObj["timestamp"]   = t.timestamp.toString(Qt::ISODate);
                txns.append(tObj);
            }
            aObj["transactions"] = txns;
            accounts.append(aObj);
        }
        obj["accounts"] = accounts;
        array.append(obj);
    }

    QFile file(m_dataPath + "/customers.json");
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
    return true;
}

QList<QSharedPointer<Customer>> Database::loadCustomers()
{
    QList<QSharedPointer<Customer>> customers;
    QFile file(m_dataPath + "/customers.json");
    if (!file.open(QIODevice::ReadOnly)) return customers;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isArray()) return customers;

    for (const auto &val : doc.array()) {
        QJsonObject obj = val.toObject();
        auto c = QSharedPointer<Customer>::create(
            obj["name"].toString(),
            obj["cnic"].toString(),
            obj["phone"].toString(),
            obj["email"].toString(),
            obj["address"].toString()
        );

        for (const auto &aVal : obj["accounts"].toArray()) {
            QJsonObject aObj = aVal.toObject();
            Account::AccountType type = Account::Savings;
            if (aObj["type"].toString() == "Current") type = Account::Current;
            else if (aObj["type"].toString() == "Fixed Deposit") type = Account::Fixed;

            auto acc = QSharedPointer<Account>::create(
                aObj["number"].toString(), c->name(), type, aObj["balance"].toDouble()
            );
            c->addAccount(acc);
        }
        customers.append(c);
    }
    return customers;
}

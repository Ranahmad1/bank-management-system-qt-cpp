#include "../include/database.h"
#include <QFile>
#include <QSaveFile>
#include <stdexcept>
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

    // QSaveFile writes to a temporary file and renames it on commit(), so a
    // crash mid-write can no longer leave a truncated customers.json behind.
    QDir().mkpath(m_dataPath);  // the folder may have been removed since startup
    QSaveFile file(m_dataPath + "/customers.json");
    if (!file.open(QIODevice::WriteOnly)) return false;
    if (file.write(QJsonDocument(array).toJson(QJsonDocument::Indented)) < 0) {
        file.cancelWriting();
        return false;
    }
    return file.commit();
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
        c->restoreIdentity(
            obj["id"].toString(),
            QDateTime::fromString(obj["registered"].toString(), Qt::ISODate)
        );

        for (const auto &aVal : obj["accounts"].toArray()) {
            QJsonObject aObj = aVal.toObject();
            Account::AccountType type = Account::Savings;
            if (aObj["type"].toString() == "Current") type = Account::Current;
            else if (aObj["type"].toString() == "Fixed Deposit") type = Account::Fixed;

            QList<Transaction> txns;
            for (const auto &tVal : aObj["transactions"].toArray()) {
                QJsonObject tObj = tVal.toObject();
                Transaction t;
                t.id           = tObj["id"].toString();
                int rawType    = tObj["type"].toInt();
                t.type         = (rawType >= Transaction::Deposit && rawType <= Transaction::Transfer)
                                     ? static_cast<Transaction::Type>(rawType)
                                     : Transaction::Deposit;
                t.amount       = tObj["amount"].toDouble();
                t.balanceAfter = tObj["balance"].toDouble();
                t.description  = tObj["description"].toString();
                t.timestamp    = QDateTime::fromString(tObj["timestamp"].toString(), Qt::ISODate);
                txns.append(t);
            }

            try {
                auto acc = QSharedPointer<Account>::create(
                    aObj["number"].toString(), c->name(), type, aObj["balance"].toDouble()
                );
                acc->restoreState(
                    QDateTime::fromString(aObj["created"].toString(), Qt::ISODate),
                    aObj["active"].toBool(true),
                    txns
                );
                c->addAccount(acc);
            } catch (const std::invalid_argument &) {
                // Corrupt record (e.g. negative balance): skip it instead of crashing on startup.
                continue;
            }
        }
        customers.append(c);
    }
    return customers;
}

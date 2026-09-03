#pragma once
#include <QString>
#include <QDateTime>

struct Transaction {
    enum Type { Deposit, Withdrawal, Transfer };

    QString   id;
    Type      type;
    double    amount;
    double    balanceAfter;
    QString   description;
    QDateTime timestamp;

    QString typeString() const;
    QString formattedAmount() const;
};

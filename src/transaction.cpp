#include "../include/transaction.h"

QString Transaction::typeString() const
{
    switch (type) {
        case Deposit:    return "Deposit";
        case Withdrawal: return "Withdrawal";
        case Transfer:   return "Transfer";
        default:         return "Unknown";
    }
}

QString Transaction::formattedAmount() const
{
    QString prefix = (type == Withdrawal || type == Transfer) ? "-" : "+";
    return prefix + "PKR " + QString::number(amount, 'f', 2);
}

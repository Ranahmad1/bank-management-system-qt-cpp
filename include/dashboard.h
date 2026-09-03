#pragma once
#include "customer.h"
#include <QWidget>
#include <QLabel>
#include <QSharedPointer>

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(const QList<QSharedPointer<Customer>> &customers,
                       QWidget *parent = nullptr);
    void refresh(const QList<QSharedPointer<Customer>> &customers);

private:
    void setupUI();
    QLabel *makeStatCard(const QString &icon, const QString &label,
                         const QString &value, const QString &color);

    QLabel *m_totalCustomers;
    QLabel *m_totalAccounts;
    QLabel *m_totalBalance;
    QLabel *m_activeAccounts;

    const QList<QSharedPointer<Customer>> *m_customers;
};

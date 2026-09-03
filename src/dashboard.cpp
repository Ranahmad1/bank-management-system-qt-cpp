#include "../include/dashboard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

Dashboard::Dashboard(const QList<QSharedPointer<Customer>> &customers, QWidget *parent)
    : QWidget(parent)
    , m_customers(&customers)
{
    setupUI();
    refresh(customers);
}

void Dashboard::setupUI()
{
    setStyleSheet("background: #0f0f1a; color: white;");

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(24, 24, 24, 24);
    root->setSpacing(20);

    QLabel *title = new QLabel("Dashboard", this);
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: white;");
    root->addWidget(title);

    // Stats grid
    QGridLayout *grid = new QGridLayout;
    grid->setSpacing(16);

    m_totalCustomers = makeStatCard("👤", "Total Customers", "0", "#3B82F6");
    m_totalAccounts  = makeStatCard("🏦", "Total Accounts",  "0", "#10B981");
    m_totalBalance   = makeStatCard("💰", "Total Balance",   "PKR 0", "#F59E0B");
    m_activeAccounts = makeStatCard("✅", "Active Accounts",  "0", "#8B5CF6");

    grid->addWidget(m_totalCustomers, 0, 0);
    grid->addWidget(m_totalAccounts,  0, 1);
    grid->addWidget(m_totalBalance,   0, 2);
    grid->addWidget(m_activeAccounts, 0, 3);

    root->addLayout(grid);
    root->addStretch();
}

QLabel *Dashboard::makeStatCard(const QString &icon, const QString &label,
                                 const QString &value, const QString &color)
{
    QWidget *card = new QWidget(this);
    card->setStyleSheet(
        "background: #1a1a2e; border-radius: 12px;"
        "border: 1px solid #2a2a45; padding: 16px;"
    );
    card->setMinimumHeight(110);

    QVBoxLayout *layout = new QVBoxLayout(card);

    QLabel *iconLabel = new QLabel(icon + "  " + label);
    iconLabel->setStyleSheet("color: #888; font-size: 13px;");

    QLabel *valueLabel = new QLabel(value);
    valueLabel->setStyleSheet("color: " + color + "; font-size: 26px; font-weight: bold;");
    valueLabel->setObjectName("value");

    layout->addWidget(iconLabel);
    layout->addWidget(valueLabel);

    // Store the value label as the card's main label
    // (We reuse the card's layout children for refresh)
    return valueLabel;
}

void Dashboard::refresh(const QList<QSharedPointer<Customer>> &customers)
{
    int totalAccounts = 0, activeAccounts = 0;
    double totalBalance = 0.0;

    for (const auto &c : customers) {
        for (const auto &acc : c->accounts()) {
            totalAccounts++;
            if (acc->isActive()) {
                activeAccounts++;
                totalBalance += acc->balance();
            }
        }
    }

    m_totalCustomers->setText(QString::number(customers.size()));
    m_totalAccounts->setText(QString::number(totalAccounts));
    m_totalBalance->setText("PKR " + QString::number(totalBalance, 'f', 0));
    m_activeAccounts->setText(QString::number(activeAccounts));
}

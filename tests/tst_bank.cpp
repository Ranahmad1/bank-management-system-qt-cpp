#include <QtTest>
#include <QDir>
#include <QStandardPaths>

#include "account.h"
#include "customer.h"
#include "database.h"

class BankTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();

    void transferMovesMoney();
    void transferToInactiveAccountIsRejectedWithoutLosingMoney();
    void transferToSameAccountIsRejected();
    void savingsMinimumBalanceIsEnforced();
    void negativeInitialBalanceThrows();

    void persistenceKeepsCustomerIdentity();
    void persistenceKeepsTransactionHistoryAndState();
};

void BankTest::initTestCase()
{
    // Keep tests away from the real application data directory.
    QStandardPaths::setTestModeEnabled(true);
}

void BankTest::init()
{
    QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).removeRecursively();
}

void BankTest::transferMovesMoney()
{
    Account a("A1", "Ali", Account::Current, 1000);
    Account b("A2", "Ali", Account::Current, 0);

    QVERIFY(a.transfer(b, 300));
    QCOMPARE(a.balance(), 700.0);
    QCOMPARE(b.balance(), 300.0);
}

void BankTest::transferToInactiveAccountIsRejectedWithoutLosingMoney()
{
    Account a("A1", "Ali", Account::Current, 1000);
    Account b("A2", "Ali", Account::Current, 0);
    b.setActive(false);

    QVERIFY(!a.transfer(b, 100));
    QCOMPARE(a.balance(), 1000.0);
    QCOMPARE(b.balance(), 0.0);
    QVERIFY(a.transactions().isEmpty());
}

void BankTest::transferToSameAccountIsRejected()
{
    Account a("A1", "Ali", Account::Current, 1000);

    QVERIFY(!a.transfer(a, 100));
    QCOMPARE(a.balance(), 1000.0);
}

void BankTest::savingsMinimumBalanceIsEnforced()
{
    Account a("S1", "Ali", Account::Savings, 600);

    QVERIFY(!a.withdraw(200));   // would leave 400 < 500 minimum
    QVERIFY(a.withdraw(100));    // leaves exactly 500
    QCOMPARE(a.balance(), 500.0);
}

void BankTest::negativeInitialBalanceThrows()
{
    QVERIFY_EXCEPTION_THROWN(Account("X", "Ali", Account::Savings, -1), std::invalid_argument);
}

void BankTest::persistenceKeepsCustomerIdentity()
{
    auto c = QSharedPointer<Customer>::create("Ali", "12345-1234567-1", "0300", "a@b.c", "Faisalabad");
    const QString id = c->customerId();

    auto &db = Database::instance();
    QVERIFY(db.saveCustomers({c}));

    auto loaded = db.loadCustomers();
    QCOMPARE(loaded.size(), 1);
    QCOMPARE(loaded[0]->customerId(), id);
    QCOMPARE(loaded[0]->name(), QString("Ali"));
}

void BankTest::persistenceKeepsTransactionHistoryAndState()
{
    auto c = QSharedPointer<Customer>::create("Ali", "12345-1234567-1", "0300", "a@b.c", "Faisalabad");
    auto a = QSharedPointer<Account>::create("A1", "Ali", Account::Current, 1000);
    auto b = QSharedPointer<Account>::create("A2", "Ali", Account::Savings, 2000);
    c->addAccount(a);
    c->addAccount(b);

    QVERIFY(a->deposit(200, "Salary"));
    QVERIFY(a->withdraw(50));
    b->setActive(false);

    auto &db = Database::instance();
    QVERIFY(db.saveCustomers({c}));

    auto loaded = db.loadCustomers();
    QCOMPARE(loaded.size(), 1);
    QCOMPARE(loaded[0]->accounts().size(), 2);

    auto la = loaded[0]->accounts()[0];
    QCOMPARE(la->balance(), a->balance());
    QCOMPARE(la->transactions().size(), 2);
    QCOMPARE(la->transactions()[0].description, QString("Salary"));
    QCOMPARE(la->transactions()[0].type, Transaction::Deposit);
    QCOMPARE(la->transactions()[1].type, Transaction::Withdrawal);

    QVERIFY(!loaded[0]->accounts()[1]->isActive());
}

QTEST_APPLESS_MAIN(BankTest)
#include "tst_bank.moc"

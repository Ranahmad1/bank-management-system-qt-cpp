#pragma once
#include "database.h"
#include "customer.h"
#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void loadData();
    void refreshCustomerTable();

    QWidget* buildCustomerPage();
    QWidget* buildAccountPage();
    QWidget* buildTransactionPage();

    Database  &m_db;
    QList<QSharedPointer<Customer>> m_customers;

    QListWidget    *m_sidebar;
    QStackedWidget *m_stack;
    QTableWidget   *m_customerTable;
    QTableWidget   *m_accountTable;
    QTableWidget   *m_transactionTable;
};

#include "../include/mainwindow.h"
#include "../include/dashboard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_db(Database::instance())
{
    setWindowTitle("Bank Management System — v1.0");
    setMinimumSize(1100, 700);
    setupUI();
    loadData();
}

MainWindow::~MainWindow()
{
    m_db.saveCustomers(m_customers);
}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Sidebar
    m_sidebar = new QListWidget(this);
    m_sidebar->setFixedWidth(200);
    m_sidebar->addItem("🏠  Dashboard");
    m_sidebar->addItem("👤  Customers");
    m_sidebar->addItem("🏦  Accounts");
    m_sidebar->addItem("💳  Transactions");
    m_sidebar->addItem("📊  Reports");
    m_sidebar->setCurrentRow(0);
    m_sidebar->setStyleSheet(
        "QListWidget { background: #1a1a2e; border: none; padding: 8px; }"
        "QListWidget::item { color: #aaa; padding: 12px 16px; border-radius: 8px; margin: 2px; }"
        "QListWidget::item:selected { background: #3B82F6; color: white; }"
        "QListWidget::item:hover { background: #2a2a45; color: white; }"
    );

    // Stack widget for pages
    m_stack = new QStackedWidget(this);
    m_stack->addWidget(new Dashboard(m_customers, this));
    m_stack->addWidget(buildCustomerPage());
    m_stack->addWidget(buildAccountPage());
    m_stack->addWidget(buildTransactionPage());

    connect(m_sidebar, &QListWidget::currentRowChanged, m_stack, &QStackedWidget::setCurrentIndex);

    QHBoxLayout *layout = new QHBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_sidebar);
    layout->addWidget(m_stack);
}

void MainWindow::loadData()
{
    m_customers = m_db.loadCustomers();
    refreshCustomerTable();
}

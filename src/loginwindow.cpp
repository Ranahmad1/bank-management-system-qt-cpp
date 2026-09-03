#include "../include/loginwindow.h"
#include "../include/mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

// Default admin credentials (in production: use hashed passwords + DB)
static const QString ADMIN_USER = "admin";
static const QString ADMIN_PASS = "admin123";

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Bank Management System — Login");
    setFixedSize(420, 520);
    setStyleSheet("background-color: #0f0f1a;");
    setupUI();
}

void LoginWindow::setupUI()
{
    QVBoxLayout *root = new QVBoxLayout(this);
    root->setAlignment(Qt::AlignCenter);

    // Card
    QWidget *card = new QWidget(this);
    card->setFixedSize(360, 440);
    card->setStyleSheet(
        "background: #1a1a2e;"
        "border-radius: 16px;"
        "border: 1px solid #2a2a45;"
    );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(40);
    shadow->setColor(QColor(59, 130, 246, 80));
    shadow->setOffset(0, 8);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(32, 40, 32, 40);
    cardLayout->setSpacing(16);

    // Logo / title
    QLabel *logo = new QLabel("🏦", card);
    logo->setAlignment(Qt::AlignCenter);
    logo->setStyleSheet("font-size: 48px; background: transparent;");

    QLabel *title = new QLabel("Bank Management", card);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: white; font-size: 20px; font-weight: bold; background: transparent;");

    QLabel *sub = new QLabel("Sign in to your account", card);
    sub->setAlignment(Qt::AlignCenter);
    sub->setStyleSheet("color: #888; font-size: 13px; background: transparent;");

    // Fields
    m_usernameEdit = new QLineEdit(card);
    m_usernameEdit->setPlaceholderText("Username");
    m_usernameEdit->setFixedHeight(44);
    m_usernameEdit->setStyleSheet(fieldStyle());

    m_passwordEdit = new QLineEdit(card);
    m_passwordEdit->setPlaceholderText("Password");
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setFixedHeight(44);
    m_passwordEdit->setStyleSheet(fieldStyle());

    m_errorLabel = new QLabel(card);
    m_errorLabel->setStyleSheet("color: #EF4444; font-size: 12px; background: transparent;");
    m_errorLabel->setAlignment(Qt::AlignCenter);
    m_errorLabel->hide();

    // Login button
    QPushButton *loginBtn = new QPushButton("Sign In", card);
    loginBtn->setFixedHeight(44);
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setStyleSheet(
        "QPushButton { background: #3B82F6; color: white; border: none;"
        "border-radius: 8px; font-size: 15px; font-weight: bold; }"
        "QPushButton:hover { background: #2563EB; }"
        "QPushButton:pressed { background: #1D4ED8; }"
    );

    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::attemptLogin);
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::attemptLogin);

    cardLayout->addWidget(logo);
    cardLayout->addWidget(title);
    cardLayout->addWidget(sub);
    cardLayout->addSpacing(8);
    cardLayout->addWidget(m_usernameEdit);
    cardLayout->addWidget(m_passwordEdit);
    cardLayout->addWidget(m_errorLabel);
    cardLayout->addWidget(loginBtn);

    root->addWidget(card, 0, Qt::AlignCenter);
}

void LoginWindow::attemptLogin()
{
    QString user = m_usernameEdit->text().trimmed();
    QString pass = m_passwordEdit->text();

    if (user == ADMIN_USER && pass == ADMIN_PASS) {
        MainWindow *mw = new MainWindow();
        mw->show();
        this->close();
    } else {
        m_errorLabel->setText("Invalid username or password");
        m_errorLabel->show();
        m_passwordEdit->clear();
        m_passwordEdit->setFocus();
    }
}

QString LoginWindow::fieldStyle() const
{
    return "QLineEdit {"
           "  background: #0f0f1a;"
           "  color: white;"
           "  border: 1px solid #2a2a45;"
           "  border-radius: 8px;"
           "  padding: 0 12px;"
           "  font-size: 14px;"
           "}"
           "QLineEdit:focus {"
           "  border: 1px solid #3B82F6;"
           "}";
}

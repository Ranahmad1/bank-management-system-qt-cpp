#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void attemptLogin();

private:
    void    setupUI();
    QString fieldStyle() const;

    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QLabel    *m_errorLabel;
};

#include "../include/loginwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Apply Fusion style for consistent cross-platform look
    app.setStyle(QStyleFactory::create("Fusion"));

    // Set application metadata
    app.setApplicationName("Bank Management System");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("MADigital");

    // Apply dark palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(30, 30, 40));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(20, 20, 30));
    darkPalette.setColor(QPalette::AlternateBase, QColor(40, 40, 55));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(45, 45, 60));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor(59, 130, 246));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    app.setPalette(darkPalette);

    LoginWindow loginWindow;
    loginWindow.show();

    return app.exec();
}

#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // translation
    QTranslator translator;
    translator.load("khrypto_pl");
    a.installTranslator(&translator);

    w.show();
    return a.exec();
}

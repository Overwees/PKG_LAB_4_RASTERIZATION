#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qApp->setStyle(QStyleFactory::create("Fusion"));
    w.setWindowTitle("Rasterization");
    w.setWindowIcon(QIcon("../Lab4/icon.png"));
    w.show();
    return a.exec();
}

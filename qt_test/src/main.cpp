#include "../include/qttest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTTest w;
    w.show();

    return a.exec();
}

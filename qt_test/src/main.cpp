
#include "../include/qttest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    qRegisterMetaType<std::string>("std::string");
    QApplication a(argc, argv);

    QTTest w;
    w.show();

    return a.exec();
}

#include "../include/qttest.h"
#include "ui_qttest.h"

QTTest::QTTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTTest)
{
    ui->setupUi(this);
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(click_send_button()));
}

void QTTest::click_send_button(){
    std::string xValue = ui->lineEditX->text().toUtf8().constData();
    std::string yValue = ui->lineEditY->text().toUtf8().constData();
    std::string zValue = ui->lineEditZ->text().toUtf8().constData();

    std::string showString;
    showString.append(xValue);
    showString.append(",");
    showString.append(yValue);
    showString.append(",");
    showString.append(zValue);

    ui->labelDescription->setText(QString::fromStdString(showString));
}
QTTest::~QTTest()
{
    delete ui;
}

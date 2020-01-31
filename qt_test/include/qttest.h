#ifndef QTTEST_H
#define QTTEST_H

#include <QMainWindow>

namespace Ui {
class QTTest;
}

class QTTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTTest(QWidget *parent = nullptr);
    ~QTTest();
private slots:
    void click_send_button();
private:
    Ui::QTTest *ui;
};

#endif // QTTEST_H

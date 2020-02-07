#include "../include/qttest.h"
#include "ui_qttest.h"

QTTest::QTTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTTest)
{
    ui->setupUi(this);
#ifndef MergeRosAndQtWay
    rosThread = new RosThread(this);
#else
    rosThread = new RosThreadAndRun(this);
#endif
    
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(click_send_button()));
    connect(this,SIGNAL(send_command_to_ros(std::string)) ,rosThread,SLOT(send_singal(std::string)));
    connect(rosThread,SIGNAL(print_meeage(std::string)),this,SLOT(show_messgae(std::string)));

    rosThread->start();

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

    emit send_command_to_ros(showString);

    ui->labelDescription->setText(QString::fromStdString(showString));
}

void QTTest::show_messgae(std::string msg){
  QMessageBox::information(NULL, tr("a msg"), tr(msg.c_str())); 
}
QTTest::~QTTest()
{
    rclcpp::shutdown();
    rosThread->exit(0);
    delete ui;
    delete rosThread;
}

#ifndef MergeRosAndQtWay

RosThread::RosThread(QObject *parent)
:QThread (parent)
{
  rosCommnad = std::make_shared<RosCommand>(std::bind(&RosThread::print_meeage, this, std::placeholders::_1));
}


void RosThread::run(){
  rclcpp::spin(rosCommnad);
}

void RosThread::send_singal(std::string msg){
  std_msgs::msg::String pubMsg;
  pubMsg.data = msg;
  rosCommnad->getPublisher()->publish(pubMsg);
}

#else
RosThreadAndRun::RosThreadAndRun(QObject *parent)
:QThread (parent)
{
  node = rclcpp::Node::make_shared("MergeRosAndQtWay");
  publisher = node->create_publisher<std_msgs::msg::String>("from_qt",rclcpp::QoS(10));
  subscription = node->create_subscription<std_msgs::msg::String>(
		"to_qt",
		10,
		[&](const std_msgs::msg::String::SharedPtr msg) ->void {
		  print_meeage(msg->data);
		}
	);
}
void RosThreadAndRun::run(){
  
  rclcpp::spin(node);
  
}
void RosThreadAndRun::send_singal(std::string msg){
  std_msgs::msg::String pubMsg;
  pubMsg.data = msg;
  publisher->publish(pubMsg);
}
#endif
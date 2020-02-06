#ifndef QTTEST_H
#define QTTEST_H

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <QMainWindow>
#include <QThread>
#include <QMessageBox>
#include <string>

namespace Ui {
class QTTest;
}

class RosCommand : public rclcpp::Node{
public:
    RosCommand(std::function<void(std::string)> handle_function)
    : Node("test_ros"),handle_function(handle_function){
      
      publisher = this->create_publisher<std_msgs::msg::String>("from_qt", 10);

      subscription = this->create_subscription<std_msgs::msg::String>(
      "to_qt", 10, std::bind(&RosCommand::topic_callback, this, std::placeholders::_1));
    }
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr getPublisher(){
        return publisher;
    }

private: 
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;
    std::function<void(std::string)> handle_function;
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
      handle_function(msg->data);
    }
    
};

class RosThread : public QThread
{

Q_OBJECT

public:
    explicit RosThread(QObject *parent = 0);
    void run();
    std::shared_ptr<RosCommand> rosCommnad;
    bool Stop;

signals:
    void print_meeage(std::string msg);

public slots:
    void send_singal(std::string);
 

};

class QTTest : public QMainWindow
{
    Q_OBJECT

public:
    RosThread *rosThread;
    explicit QTTest(QWidget *parent = nullptr);
    ~QTTest();
private slots:
    void click_send_button();
    void show_messgae(std::string msg);
signals:
    void send_command_to_ros(std::string);
private:
    Ui::QTTest *ui;
};




#endif // QTTEST_H

import rclpy
import my_msgs

from rclpy.node import Node

from python_test_msg.msg import PythonTalker

class Talker(Node):

    def __init__(self):
        super().__init__('talker')
        self.counter = 0
        self.publisher = self.create_publisher(PythonTalker, 'my_python_msg_test', 10)
        timer_period = 1.0
        self.tmr = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        msg = PythonTalker()
        msg.data = "Hello World!"
        msg.talk_times = self.counter
        self.counter += 1
        self.get_logger().info('Publishing something !')
        self.publisher.publish(msg)


def main(args=None):
    rclpy.init(args=args)

    node = Talker()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
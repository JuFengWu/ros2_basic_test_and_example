import rclpy
from rclpy.node import Node

from python_test_msg.msg import PythonTalker


class Listener(Node):

    def __init__(self):
        super().__init__('listener')
        self.subscription = self.create_subscription(
            PythonTalker,
            'my_python_msg_test',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s" , and the send times is %d' % (msg.data,msg.talk_times))


def main(args=None):
    rclpy.init(args=args)

    listener = Listener()

    rclpy.spin(listener)

    listener.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
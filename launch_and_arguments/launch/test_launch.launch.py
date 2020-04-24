import sys
import os
import launch
from ament_index_python.packages import get_package_share_directory,get_package_prefix
from launch import LaunchDescription
from launch.actions.execute_process import ExecuteProcess
from launch_ros.actions import Node


def generate_launch_description():

    ld = LaunchDescription([
        #Node(package = 'cut_simulator', node_executable = 'cut_simulator_node', output = 'screen'),
        Node(package = 'launch_and_arguments', node_executable='talker', output='screen',arguments=['123']),
        Node(package = 'launch_and_arguments', node_executable='listener', output='screen',on_exit=[
                    launch.actions.LogInfo(
                        msg = "Listener exited; tearing down entire system."),
                    launch.actions.EmitEvent(
                        event = launch.events.Shutdown())])
        ])

    return ld
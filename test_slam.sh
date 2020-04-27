#!/bin/sh
xterm  -e  " source ~/catkin_ws/devel/setup.bash; killall gzserver; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5
xterm  -e  " source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 5
xterm  -e  " source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch  " &
sleep 5
xterm  -e  " source ~/catkin_ws/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch "

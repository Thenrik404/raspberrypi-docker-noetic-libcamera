#!/bin/bash

# Copy the default configuration if it doesn't exist
# if [ -z "$(ls -A /root/catkin_ws)" ]; then
#   echo "volume is empty... copying ros2_ws_backup to ros2_ws"
#   cp -r /root/catkin_ws_backup/. /root/catkin_ws
# fi

cd /root/catkin_ws && . install/setup.bash
# source ros
source /opt/ros/${ROS_DISTRO}/setup.bash
# Run the main container command
exec "$@"
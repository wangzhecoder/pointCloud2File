cmake_minimum_required(VERSION 2.8.3)
project(p2f)

## Find catkin and any catkin packages
find_package(catkin REQUIRED 
	COMPONENTS 
		roscpp 
		rospy 
		sensor_msgs 
		pcl_ros
)
#find_package(pcl)

## Generate added messages and services
generate_messages(DEPENDENCIES 
	sensor_msgs
)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(point2File src/p2f.cpp)
target_link_libraries(point2File ${catkin_LIBRARIES})

/*
 * p2f.cpp
 *
 *  Created on: 2017年7月20日
 *      Author: wz
 */
#include "ros/ros.h"
#include "ros/console.h"
#include <sensor_msgs/PointCloud2.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/ply_io.h>
#include <iostream>
#include <string>

class p2f{
	public:
		p2f();
		void rslidar_pointCloud2File(const sensor_msgs::PointCloud2ConstPtr & cloud_msg);
		void velodyne_pointCloud2File(const sensor_msgs::PointCloud2ConstPtr & cloud_msg);
	private:
		ros::NodeHandle _nh;
		ros::Subscriber rslidar_pointCloud2_sub;
		ros::Subscriber velodyne_pointCloud2_sub;
		long frameNum;
};

p2f::p2f()
	:frameNum(0)
{
	rslidar_pointCloud2_sub = _nh.subscribe("rslidar_points",1,&p2f::rslidar_pointCloud2File,this);
	velodyne_pointCloud2_sub = _nh.subscribe("velodyne_points",1,&p2f::velodyne_pointCloud2File,this);
}

void p2f::rslidar_pointCloud2File(const sensor_msgs::PointCloud2ConstPtr & cloud_msg)
{
	if(frameNum%100 == 0)
	{
		pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
		pcl_conversions::toPCL(*cloud_msg,*cloud);
		std::string fileNames = "rslidar-";
		std::stringstream ss;
		std::string num;
		ss<<frameNum;ss>>num;
		fileNames = fileNames+num+".ply";
		pcl::io::savePLYFile(fileNames,*cloud);
		ROS_INFO("rslidar saved");
	}
	frameNum++;
}

void p2f::velodyne_pointCloud2File(const sensor_msgs::PointCloud2ConstPtr & cloud_msg)
{
	pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
	pcl_conversions::toPCL(*cloud_msg,*cloud);
	pcl::io::savePLYFile("myPLY_velodyne.ply",*cloud);
	ROS_INFO("velodyne saved");
}

int main(int argc,char** argv)
{
	ros::init(argc,argv,"p2f");
	p2f p;
	ros::spin();
	return 0;
}




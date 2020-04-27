#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"

bool picked = false;
bool dropped = false;
bool temp1 = true;
bool temp2 = true;

void callback(const nav_msgs::Odometry::ConstPtr& msg)
{
  float cur_x = 0;
  float cur_y = 0;

  cur_x = msg->pose.pose.position.x ;
  cur_y = msg->pose.pose.position.y ;
  // ROS_INFO("I heard: [%f], [%f]", cur_x, cur_y);

  if((cur_x < 0.5 && cur_x > -0.5) && (cur_y < -2.5 && cur_y > -3.5) && temp1 == true){
    picked = true;
    temp1 = false;
    ROS_INFO("first loop");
  }

  if((cur_x < 3.5 && cur_x > 2.5) && (cur_y < -2.1 && cur_y > -3.5) && temp2 == true){
    dropped = true;
    temp2 = false;
    ROS_INFO("second loop");
  }

}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Subscriber obom_sub = n.subscribe("/odom", 1000, callback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  ros::Rate r(1);
  visualization_msgs::Marker marker;

  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.id = 0;

  marker.type = visualization_msgs::Marker::CUBE;
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 0.2;
  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();

  while (ros::ok()){
    // ROS_INFO("in loop");
    if (!picked){
      marker.action = visualization_msgs::Marker::ADD;
      ROS_INFO("first condition");
      marker.pose.position.x = 0;
      marker.pose.position.y = -3.0;
      marker_pub.publish(marker);
      // ros::Duration(5).sleep();
    }else{
      ROS_INFO("middle condition");
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      // ros::Duration(5).sleep();
    }

    if(dropped){
      marker.action = visualization_msgs::Marker::ADD;
      ROS_INFO("Last condition");
      marker.pose.position.x = 3.0;
      marker.pose.position.y = -3.0;
      marker_pub.publish(marker);
      ros::Duration(5.0).sleep();
    }
    // ros::waitForShutdown();
    ros::spinOnce();


  }


  return 0;
}

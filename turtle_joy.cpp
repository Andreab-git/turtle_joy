/* Move the turtle using publisher and subscriber in the same node

  author : Andrea Bena'
  version: 1.0
  date   : 07/01/2021

*/
#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

#define INCREMENT 4


float move = 0, angle = 0;
ros::Publisher pub;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg) {
  move = msg->axes[1];
  angle = msg->axes[2];
}


int main(int argc, char **argv) {
  
  ros::init(argc, argv, "turtle_joy");
  ros::NodeHandle node;

  pub = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);
  ros::Subscriber sub = node.subscribe("/joy", 100, joyCallback);

  ros::Rate loop(10);

  int count = 0;

  while(ros::ok()) {

    geometry_msgs::Twist m;
    m.linear.x = move*INCREMENT;
    m.linear.y = 0;
    m.linear.z = 0;

    m.angular.x = 0;
    m.angular.y = 0;
    m.angular.z = angle*INCREMENT;

    pub.publish(m);

    ros::spinOnce();
    loop.sleep();
    count++;
    
  }
  
  return 0;
}





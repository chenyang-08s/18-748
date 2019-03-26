#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Imu.h"

#include <sstream>

static geometry_msgs::Quaternion createQuaternionFromRPY(double roll, double pitch, double yaw) {
    geometry_msgs::Quaternion q;
    double t0 = cos(yaw * 0.5);
    double t1 = sin(yaw * 0.5);
    double t2 = cos(roll * 0.5);
    double t3 = sin(roll * 0.5);
    double t4 = cos(pitch * 0.5);
    double t5 = sin(pitch * 0.5);
    q.w = t0 * t2 * t4 + t1 * t3 * t5;
    q.x = t0 * t3 * t4 - t1 * t2 * t5;
    q.y = t0 * t2 * t5 + t1 * t3 * t4;
    q.z = t1 * t2 * t4 - t0 * t3 * t5;
    return q;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<sensor_msgs::Imu>("imu", 1000);

  ros::Rate loop_rate(1);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
    sensor_msgs::Imu msg;
    geometry_msgs::Vector3 linear;
    linear.x = 0;
    linear.y = 0;
    linear.z = 0;
    geometry_msgs::Vector3 angular;
    angular.x = 0;
    angular.y = 0;
    angular.z = 0;
    /*geometry_msgs::Quaternion quaternion;
    quaternion.x = 0;
    quaternion.y = 0;
    quaternion.z = 0;
    quaternion.w = 0;*/
    float yaw = 0;
    float pitch = 0;
    float roll = 0;
    msg.orientation = createQuaternionFromRPY(roll,pitch,yaw);
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    
    yaw += 0.1;
    if(yaw >= 6.28){
      yaw = 0;
    }
    ROS_INFO("%f", yaw);
    msg.orientation = createQuaternionFromRPY(roll,pitch,yaw);
    
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}

#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from sensor_msgs.msg import Imu
from tf.transformations import quaternion_from_euler

def talker():
    pub = rospy.Publisher('imu', Imu, queue_size=10)
    rospy.init_node('talker_py', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    roll,pitch,yaw = 0,0,0
    while not rospy.is_shutdown():
        #time = rospy.get_time()
        imuMsg = Imu()
        # linear
        imuMsg.linear_acceleration.x = 0
        imuMsg.linear_acceleration.y = 0
        imuMsg.linear_acceleration.z = 0
        # gyro
        imuMsg.angular_velocity.x = 0
        imuMsg.angular_velocity.y = 0
        imuMsg.angular_velocity.z = 0
        # quaternion
        q = quaternion_from_euler(roll,pitch,yaw)
        imuMsg.orientation.x = q[0]
        imuMsg.orientation.y = q[1]
        imuMsg.orientation.z = q[2]
        imuMsg.orientation.w = q[3]


        imuMsg.header.stamp= rospy.Time.now()
        #rospy.loginfo(imuMsg)
        pub.publish(imuMsg)
        yaw += 0.01
        if(yaw >= 6.28):yaw = 0
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass

#include <lccv.hpp>
#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "sensor_msgs/Image.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;
    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);
    ros::Publisher image_pub = nh.advertise<sensor_msgs::Image>("image_topic", 1);

    cv::Mat image;
    lccv::PiCamera cam;
    cam.options->photo_width=1024;
    cam.options->photo_height=768;
    cam.options->verbose=true;
    for(int i=0;i<1;i++){
        std::cout<<i<<std::endl;
        if(!cam.capturePhoto(image)){
            std::cout<<"Camera error"<<std::endl;
        }
        cv::imwrite("/home/docker/catkin_ws/src/camera/images/test.jpg", image);
    }

    cv_bridge::CvImage cv_image;
    cv_image.encoding = "bgr8"; // Assuming your OpenCV image is in BGR format
    cv_image.image = image;
    sensor_msgs::ImagePtr ros_image = cv_image.toImageMsg();
    ros::Rate loop_rate(10);
    int count = 0;
    while (ros::ok())
    {
        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world " << count;
        msg.data = ss.str();
        ROS_INFO("%s", msg.data.c_str());
        chatter_pub.publish(msg);
        image_pub.publish(ros_image);
        ros::spinOnce();
        loop_rate.sleep();
        count++;
    }
}

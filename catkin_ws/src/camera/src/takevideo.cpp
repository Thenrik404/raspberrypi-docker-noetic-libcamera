#include <lccv.hpp>
#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "sensor_msgs/Image.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include <chrono>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rpi5cam");
    ros::NodeHandle nh;
    ros::Publisher image_pub = nh.advertise<sensor_msgs::Image>("image_topic", 1);
    cv::Mat image;
    lccv::PiCamera cam;
    cam.options->video_width=1280;
    cam.options->video_height=720;
    cam.options->framerate=30;
    cam.options->verbose=true;
    cam.startVideo();
    int ch=0;
    int count = 0;
    while(ch!=27 && ros::ok()){
        auto t_start = std::chrono::high_resolution_clock::now();
        if(!cam.getVideoFrame(image, 1000)){
            std::cout<<"Timeout error"<<std::endl;
        }
        else{
            cv_bridge::CvImage cv_image;
            cv_image.encoding = "bgr8"; // Assuming your OpenCV image is in BGR format
            cv_image.image = image;
            sensor_msgs::ImagePtr ros_image = cv_image.toImageMsg();
            image_pub.publish(ros_image);
            ros::spinOnce();
            auto t_end = std::chrono::high_resolution_clock::now();
            double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
            ROS_INFO_STREAM(1/(elapsed_time_ms/1000));
        }
    }
    cam.stopVideo();
}


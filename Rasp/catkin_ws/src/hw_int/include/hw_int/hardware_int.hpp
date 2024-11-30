#ifndef HARDWARE_INT_HPP
#define HARDWARE_INT_HPP

#include <hardware_interface/robot_hw.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <controller_manager/controller_manager.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Vector3.h>
#include <tf/transform_broadcaster.h>

#include <chrono> 
#include <thread> 

#include "hw_int/velocidades.h" 
#include "hw_int/encoder.h" 

#define HW_IF_UPDATE_RATE 100.0;

class Robot_HW_INT : public hardware_interface :: RobotHW
{
public: 
    Robot_HW_INT(ros::NodeHandle &nh);   
    void init();
    void encoderCallback(const hw_int::encoder::ConstPtr &msg); 
    void cmdCallback(const geometry_msgs::Twist::ConstPtr &vel); 
    void publica_vel();
protected:
    hardware_interface::JointStateInterface joint_state_interface_;
    hardware_interface::VelocityJointInterface velocity_joint_interface_;

    struct Joint
    {
        double position;
        double velocity; // só usa isso
        double effort;
        double velocity_command;
    } joints_[2]; 

    float velocidade_esq, velocidade_dir;
    ros::NodeHandle nh_;
    ros::Subscriber sub_encoder;
    ros::Subscriber sub_vel;
    ros::Publisher pub_vel;
    ros::Publisher pub_odom;
    ros::Duration elapsed_time_;        
    ros::Time current_time_;
    ros::Time last_time_;
    boost::shared_ptr<controller_manager::ControllerManager> controller_manager_;
    double loop_hz_ = HW_IF_UPDATE_RATE;
};

#endif
#include "hw_int/hardware_int.hpp"

Robot_HW_INT::Robot_HW_INT(ros::NodeHandle &nh) : nh_(nh)
{
    init();
    controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));
    controller_manager_->update(ros::Time::now(), elapsed_time_);
}

void Robot_HW_INT::init()
{
    /* Subscrito no tópico do encoder e cmd_vel (recebe velocidade alvo em Twist)
       Publica nos tópicos de velocidade (rad/s) e de odometria */
    sub_encoder = nh_.subscribe("/encoder_data", 100, &Robot_HW_INT::encoderCallback, this);
    sub_vel = nh_.subscribe("/cmd_vel", 100, &Robot_HW_INT::cmdCallback, this);
    pub_vel = nh_.advertise<hw_int::velocidades>("/velocity_cmd", 1);
    pub_odom = nh_.advertise<nav_msgs::Odometry>("/odom", 1);

    current_time_ = ros::Time::now();
    last_time_ = ros::Time::now();

    // Para cada junta
    for (int i = 0; i < 2; i++)
    {
        /*
            JointStateHandle: é usado para representar o estado de uma junta, APENAS LÊ as variáveis
            JointHandle: é usado para enviar comandos para a junta, depende das informações do estado da junta (JointStateHandle)
        */

        // junta1 e junta2
        std::string joint_name = "junta" + std::to_string(i + 1);

        hardware_interface::JointStateHandle joint_state_handle(joint_name, &joints_[i].position, &joints_[i].velocity, &joints_[i].effort);
        joint_state_interface_.registerHandle(joint_state_handle);

        hardware_interface::JointHandle joint_handle(joint_state_handle, &joints_[i].velocity_command);
        velocity_joint_interface_.registerHandle(joint_handle);
    }

    registerInterface(&joint_state_interface_);
    registerInterface(&velocity_joint_interface_);
}

// Parâmetros do robô
const double WHEEL_RADIUS = 0.049025; // Raio da roda em metros
const double WHEEL_BASE = 0.283;   // Distância entre as rodas em metros

// Variáveis globais para odometria acumulada
double x = 0.0, y = 0.0, theta = 0.0;
ros::Time last_time;

// Callback para o tópico "encoder_data"
void Robot_HW_INT::encoderCallback(const hw_int::encoder::ConstPtr &msg){
    static tf::TransformBroadcaster odom_broadcaster;

    // Velocidades angulares das rodas em rad/s
    double left_wheel_speed = msg->encoder_esq;
    double right_wheel_speed = msg->encoder_dir;

    double dt = 1/20; // considerando uma frequencia de 20hz

    // Velocidades lineares das rodas
    double v_left = left_wheel_speed * WHEEL_RADIUS;
    double v_right = right_wheel_speed * WHEEL_RADIUS;

    // Velocidade linear e angular do robô
    double linear_velocity = (v_left + v_right) / 2.0;
    double angular_velocity = (v_right - v_left) / WHEEL_BASE;

    // Atualização da posição acumulada
    theta += angular_velocity * dt;
    double dx = linear_velocity * cos(theta) * dt;
    double dy = linear_velocity * sin(theta) * dt;
    x += dx;
    y += dy;

    // Publicação da mensagem de odometria
    ros::Time current_time = ros::Time::now();
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    // Pose
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(theta);

    // Twist
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = linear_velocity;
    odom.twist.twist.angular.z = angular_velocity;

    pub_odom.publish(odom);

    // Publicação do tf
    geometry_msgs::TransformStamped odom_tf;
    odom_tf.header.stamp = current_time;
    odom_tf.header.frame_id = "odom";
    odom_tf.child_frame_id = "base_link";
    odom_tf.transform.translation.x = x;
    odom_tf.transform.translation.y = y;
    odom_tf.transform.translation.z = 0.0;
    odom_tf.transform.rotation = odom.pose.pose.orientation;

    odom_broadcaster.sendTransform(odom_tf);
}


void Robot_HW_INT::cmdCallback(const geometry_msgs::Twist::ConstPtr &vel){

    float vel_linear = vel->linear.x; 
    float vel_angular = vel->angular.z;

    // acrescentar dados para raio e largura do robo

    float r =  1.0; // raio da roda
    float b = 1.0; // largura entre rodas

    float vel_dir = ((vel_linear+(vel_angular*(b/2)))/r);
    float vel_esq = ((vel_linear-(vel_angular*(b/2)))/r);

    // atualiza os atributos
    velocidade_dir = vel_dir;
    velocidade_esq = vel_esq;
}

void Robot_HW_INT::publica_vel(){
    
    hw_int::velocidades msg;
    msg.vel_esq = velocidade_esq;
    msg.vel_dir = velocidade_dir;

    pub_vel.publish(msg);
    velocidade_dir = 0;
    velocidade_esq = 0;
}


int main(int argc, char **argv)
{
    // inicializa o nó
    ros::init(argc, argv, "hardware_int");

    // cria um NodeHandle e chama o construtor da classe
    ros::NodeHandle nh;
    Robot_HW_INT robot_hw(nh);

    ros::Rate rate(10);

    // Loop principal
    while (ros::ok())
    {
        robot_hw.publica_vel();

        ros::spinOnce();
        rate.sleep();
    }

    ros::MultiThreadedSpinner spinner(2);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
    spinner.spin();

    return 0;
}
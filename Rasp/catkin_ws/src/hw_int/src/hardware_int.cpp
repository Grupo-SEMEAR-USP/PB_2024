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
    // sub_ = nh_.subscribe("/encoder_data", 100, &Robot_HW_INT::encoderCallback, this);
    sub_ = nh_.subscribe("/cmd_vel", 100, &Robot_HW_INT::cmdCallback, this);
    pub_vel = nh_.advertise<hw_int::velocidades>("/velocity_cmd", 1);
    pub_odom = nh_.advertise<hw_int::velocidades>("/odom", 1);

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

// void Robot_HW_INT::encoderCallback(const robot_control::encoder_data::ConstPtr &msg)
// {
//     double data[2];
    
//     // Dados dos encoderes
//     data[0] = msg->front_left_encoder_data;
//     data[1] = msg->front_right_encoder_data;
  

//     std::cout << "Data: " << data[0] << " " << data[1] << std::endl;

//     current_time_ = ros::Time::now();
//     elapsed_time_ = current_time_ - last_time_;

//     // Atualiza a velocidade das juntas de acordo com o tempo passado e posição atual
//     joints_[0].velocity = data[0] / elapsed_time_.toSec();
//     joints_[1].velocity = data[1] / elapsed_time_.toSec();
    

//     robot_control::velocity_data velocity_msg;

//     // acho que aqui deveria vir o cálculo do pid?

//     velocity_msg.front_left_velocity = joints_[0].velocity_command;
//     velocity_msg.front_right_velocity = joints_[1].velocity_command;
  
//     // Publica a velocidade dos motores ()
//     // pub_.publish(velocity_msg);

//     std::cout << "Velocity: " << velocity_msg.front_left_velocity << " " << velocity_msg.front_right_velocity << " " << velocity_msg.rear_left_velocity << " " << velocity_msg.rear_right_velocity << std::endl;

//     last_time_ = current_time_;

//     controller_manager_->update(ros::Time::now(), elapsed_time_);
// }


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

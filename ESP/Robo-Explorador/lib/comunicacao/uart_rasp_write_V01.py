#!/usr/bin/env python
import rospy
import serial
from hw_int.msg import velocidades  # Certifique-se de que a mensagem "velocidades" está corretamente configurada no seu pacote ROS

# Configura a porta serial
ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)

def send_data(vel_esq, vel_dir):
    """
    Envia os dados de velocidade via UART para a ESP32.
    """
    command = f"{vel_esq},{vel_dir}\n"
    ser.write(command.encode())
    rospy.loginfo(f"Números enviados: {vel_esq} e {vel_dir}")

def velocity_cmd_callback(msg):
    """
    recebe os dados do tópico velocity_cmd e os envia via UART.
    """
    vel_esq = msg.vel_esq  # Velocidade do motor esquerdo
    vel_dir = msg.vel_dir  # Velocidade do motor direito
    send_data(vel_esq, vel_dir)

def main():
    """
    Inicializa o nó ROS e subscreve no tópico velocity_cmd.
    """
    rospy.init_node("uart_sender", anonymous=True)
    rospy.Subscriber("/velocity_cmd", velocidades, velocity_cmd_callback)
    
    rospy.loginfo("Nó UART iniciado e subscrito no tópico /velocity_cmd.")
    
    rospy.spin()  # Mantém o nó em execução

if _name_ == "_main_":
    try:
        main()
    except rospy.ROSInterruptException:
        pass
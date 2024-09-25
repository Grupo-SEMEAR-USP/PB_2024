import serial
import time

# Configura a porta serial (ajuste '/dev/ttyS0' conforme necessário)
ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
x = 0 # constante inicial
y = 1 # constante inicial

def send_data(x,y):

    motor_speed_01 = x  # Número a ser enviado (velocidade do motor, por exemplo)
    motor_speed_02 = y  # Número a ser enviado (velocidade do motor, por exemplo)
    ser.write(f"{motor_speed_01}, {motor_speed_02}\n".encode())  # Envia o número convertido para string via UART
    print(f"Números enviados: {motor_speed_01} e {motor_speed_02}")

while True:
    send_data(x,y) #envia os números
    x += 1 # adiciona 1 unidade a constante
    y += 2 # adiciona 2 unidade a constante
    time.sleep(0.07)  # Envia o número a cada 0,07 tempos
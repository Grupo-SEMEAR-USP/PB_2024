import serial
import time

# Configura a porta serial (verifique o nome da porta conforme necessário)
try:
    ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)  # Altere a porta se necessário
except serial.SerialException as e:
    print(f"Erro ao abrir a porta serial: {e}")
    exit()

# Função para receber os dados
def receive_data():
    while True:
        try:
            if ser.in_waiting > 0:
                # Lê os dados recebidos pela UART
                data = ser.readline().decode('utf-8').strip()
                
                # Separa as duas velocidades
                try:
                    motor_speed1, motor_speed2 = map(float, data.split())
                    print(f"Dados recebidos: Motor 1 = {motor_speed1}, Motor 2 = {motor_speed2}")
                except ValueError:
                    print("Erro ao processar os dados recebidos.")
        except serial.SerialException as e:
            print(f"Erro na comunicação serial: {e}")
            time.sleep(1)  # Espera antes de tentar novamente

# Inicia o recebimento dos dados
if __name__ == "__main__":
    print("Aguardando dados do ESP32...")
    receive_data()


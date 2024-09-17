import serial

# Configuração da porta serial (ajuste '/dev/ttyUSB0' ou outro conforme necessário)
ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)

while True:
    if ser.in_waiting > 0:
        try:
            # Recebe os dados como bytes brutos
            raw_data = ser.readline()  # Mantém os dados como bytes
            print(f"Bytes recebidos: {raw_data}")

            # Tenta decodificar como UTF-8, se possível
            try:
                motor_speed = raw_data.decode('utf-8')
                print(f"Número recebido: {motor_speed}")
            except UnicodeDecodeError:
                print("Erro ao decodificar os dados recebidos")

        except Exception as e:
            print(f"Erro: {e}")

#include "uart_esp32_read.h"

// Função para inicializar a UART
void uart_init() {
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_PORT_NUM, BUF_SIZE, 0, 0, NULL, 0);
}


// Função para receber os dados enviados pela Raspberry Pi
void receive_data() {
    uint8_t data[BUF_SIZE];
    int len = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE - 1, 100 / portTICK_PERIOD_MS);
    
    if (len > 0) {
        data[len] = '\0';  // Garante que o buffer de dados seja uma string válida

        // Converte os dados para string e separa em dois valores
        char *token = strtok((char *)data, ",");  // Primeiro valor antes da vírgula
        if (token != NULL) {
           float motor_1 = atof(token);  // Converte para float
        }

        token = strtok(NULL, ",");  // Segundo valor depois da vírgula
        if (token != NULL) {
           float motor_2 = atof(token);  // Converte para float
        }

        // Agora motor_1 e motor_2 têm os valores recebidos e convertidos para float
        //ESP_LOGI(TAG, "Motor 1: %f, Motor 2: %f", motor_1, motor_2);
    }
}


void app_main(void) {
    uart_init();  // Inicializa a UART

    while (1) {
        receive_data();  // Chama a função para receber dados
        vTaskDelay(100 / portTICK_PERIOD_MS);  // Atraso de 2 segundos
    }
}

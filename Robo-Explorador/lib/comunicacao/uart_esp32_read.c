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

//Código antigo que convertia os dados recebidos para inteira
/*// Função para receber os dados enviados pela Raspberry Pi
void receive_data() {
    uint8_t data[BUF_SIZE];
    int len = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE - 1, 20 / portTICK_PERIOD_MS);
    
    if (len > 0) {
        data[len] = '\0';  // Garante que o buffer de dados seja uma string válida
        int received_number = atoi((char *)data);  // Converte o valor recebido para inteiro
        ESP_LOGI(TAG, "Números recebidos da Raspberry Pi: %d", received_number);
    }
}


void app_main(void) {
    uart_init();  // Inicializa a UART

    while (1) {
        receive_data();  // Chama a função para receber dados
        vTaskDelay(20 / portTICK_PERIOD_MS);  // Atraso de 2 segundos (opcional)
    }
}*/


// Função para receber os dados enviados pela Raspberry Pi
void receive_data() {
    uint8_t data[BUF_SIZE];
    int len = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE - 1, 100 / portTICK_PERIOD_MS);
    
    if (len > 0) {
        data[len] = '\0';  // Garante que o buffer de dados seja uma string válida
        ESP_LOGI(TAG, "Dados recebidos da Raspberry Pi: %s", data);
    }
}

void app_main(void) {
    uart_init();  // Inicializa a UART

    while (1) {
        receive_data();  // Chama a função para receber dados
        vTaskDelay(100 / portTICK_PERIOD_MS);  // Atraso de 2 segundos
    }
}

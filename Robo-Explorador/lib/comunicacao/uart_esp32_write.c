#include "uart_esp32_write.h"
void uart_init() {
    // Configura os parâmetros da UART
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    
    // Inicializa a UART com os parâmetros configurados
    uart_param_config(UART_PORT_NUM, &uart_config);
    
    // Define os pinos de TX e RX
    uart_set_pin(UART_PORT_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    
    // Instala o driver UART
    uart_driver_install(UART_PORT_NUM, BUF_SIZE, 0, 0, NULL, 0);
}

void send_data() {
    float motor_speed1 = x;  // Velocidade do motor 1
    float motor_speed2 = y;  // Velocidade do motor 2
    char data_to_send[100]; // [20] é o tamanho do buffer para suportar os dois valores

    // Concatena as duas velocidades em um float, separadas por vírgula
    snprintf(data_to_send, sizeof(data_to_send), "%f %f\n", motor_speed1, motor_speed2);
    
    // Envia os dados pela UART
    uart_write_bytes(UART_PORT_NUM, data_to_send, strlen(data_to_send));
    ESP_LOGI(TAG, "Dados enviados para Raspberry Pi: %s", data_to_send);
}

void app_main(void) {
    // Inicializa a UART
    uart_init();
    
    while (1) {
        // Envia os dados a cada 20ms
        send_data();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}


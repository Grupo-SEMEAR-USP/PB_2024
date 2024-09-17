#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include <string.h>

#define TXD_PIN (17) // Pino TX GPIO_NUM_17
#define RXD_PIN (16) // Pino RX GPIO_NUM_16
#define UART_PORT_NUM UART_NUM_1
#define BUF_SIZE (1024)

static const char *TAG = "UART_ESP32";

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
    int motor_speed = 120;  // Velocidade do motor a ser enviada
    char data_to_send[10];
    
    // Converte o número para string
    snprintf(data_to_send, sizeof(data_to_send), "%d", motor_speed);
    
    // Envia os dados pela UART
    uart_write_bytes(UART_PORT_NUM, data_to_send, strlen(data_to_send));
    ESP_LOGI(TAG, "Número enviado para Raspberry Pi: %s", data_to_send);
}

void app_main(void) {
    // Inicializa a UART
    uart_init();
    
    while (1) {
        // Envia o dado a cada 2 segundos
        send_data();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include <string.h>
#include <stdlib.h>

#define TXD_PIN (17) // Pino TX GPIO_NUM_17
#define RXD_PIN (16) // Pino RX GPIO_NUM_16
#define UART_PORT_NUM UART_NUM_1
#define BUF_SIZE (1024)

static const char *TAG = "UART_ESP32";

void uart_init();
void receive_data();
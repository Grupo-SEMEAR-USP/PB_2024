#include "encoder.h"
#include "pwm_hbridge.h"

// Este programa coleta os sinais de um encoder em um intervalo de tempo e permite a vizualição dos ticks

void app_main(void){
    pcnt_unit_handle_t encoder = init_encoder(ENC_RIGHT);
    while(true){
        pulse_count(encoder);
        vTaskDelay(3);
    }
}
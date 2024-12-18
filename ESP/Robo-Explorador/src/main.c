#include "h_bridge.h" //inclui biblioteca local
#include "encoder.h"
#include "pid.h"
#include "pid_ctrl.h"
#include "uart_esp32_read.h"
#include <stdlib.h>

static const char *TAG_MAIN = "main";

pid_ctrl_block_handle_t pid_right, pid_left;
pcnt_unit_handle_t encoderR, encoderL;

// Função para testar a leitura do encoder VS PWM aplicada
void teste_encoderXpwm(){
    while(true){
        update_motor(MOTOR_RIGHT, 500); //testa leitura do encoder com 500 no pwm
        vTaskDelay(500 / portTICK_PERIOD_MS);
        for(int i=0; i<15; i++){
            pulse_count(encoderR, ENCODER_RIGHT);   // cerca de 90
        }
        update_motor(MOTOR_RIGHT, 1023); //testa com 1023
        vTaskDelay(500 / portTICK_PERIOD_MS);
        for(int i=0; i<15; i++){
            pulse_count(encoderR, ENCODER_RIGHT);   //cerca de 191
        }
    }
}

void init_all(){
    init_gpio(MOTOR_RIGHT);
    init_gpio(MOTOR_LEFT);

    init_pwm(MOTOR_RIGHT);
    init_pwm(MOTOR_LEFT);

    pid_right =  init_pid(MOTOR_RIGHT);
    pid_left = init_pid(MOTOR_LEFT);

    encoderR = init_encoder(ENCODER_RIGHT);
    encoderL = init_encoder(ENCODER_LEFT);
}

void app_main() {
    init_all();

    //vTaskDelay(5000/portTICK_PERIOD_MS); //delay de 5s para dar tempo de rodar o programa de plotar gráfico

    float valpidR = 0, valpidL = 0, setPoint = 1023, i=0;
    while(1)
    {
        // Teste PID: (funciona)
        if(i < 200) setPoint = 0;
        else setPoint = 1023;

        if(i > 400) i = 0;

        pid_apply(&valpidR, pid_right, MOTOR_RIGHT, encoderR, setPoint);
        pid_apply(&valpidL, pid_left, MOTOR_LEFT, encoderL, setPoint);
        i++;
    }
}
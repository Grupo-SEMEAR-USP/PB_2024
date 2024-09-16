#include "h_bridge.h" //inclui biblioteca local
#include "encoder.h"
#include "pid.h"
#include "pid_ctrl.h"

pid_ctrl_block_handle_t pid_right, pid_left;
pcnt_unit_handle_t encoderR, encoderL;

void testePWM(type_side_motor motor){
    int maxRes = 1023; //valor do duty cycle em 100%

    /* Loop para testar o pwm */
    while(1){ 

        //DIREÇÃO 1
        for(int i=0; i<=maxRes; i+=100){    // varia de 0 a 1023
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        for(int i=maxRes; i>=0; i-=100){    // varia de 1023 a 0
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        //DIREÇÃO 2
        for(int i=0; i>=-maxRes; i-=100){   //varia de 0 a -1023
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        for(int i=-maxRes; i<=0; i+=100){   //varia de -1023 a 0
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void init_all(){
    init_gpio(MOTOR_RIGHT);
    //init_gpio(MOTOR_LEFT);

    init_pwm(MOTOR_RIGHT);
    //init_pwm(MOTOR_LEFT);
    
    pid_right =  init_pid(MOTOR_RIGHT);
    //pid_left = init_pid(MOTOR_LEFT);

    encoderR = init_encoder(ENCODER_RIGHT);
    //encoderL = init_encoder(ENCODER_LEFT);
}

void app_main() {
    init_all();

    //TESTE ENCODER VS PWM
    // while(true){
    //     update_motor(MOTOR_RIGHT, 500); //testa leitura do encoder com 500 no pwm
    //     vTaskDelay(500 / portTICK_PERIOD_MS);
    //     for(int i=0; i<15; i++){
    //         pulse_count(encoderR);   // cerca de 90
    //     }
    //     update_motor(MOTOR_RIGHT, 1023); //testa com 1023
    //     vTaskDelay(500 / portTICK_PERIOD_MS);
    //     for(int i=0; i<15; i++){
    //         pulse_count(encoderR);   //cerca de 191
    //     }
    // }

    float valpid = 0;
    while (1){
        pid_apply(&valpid, pid_right, MOTOR_RIGHT, encoderR, 120);
    }
}
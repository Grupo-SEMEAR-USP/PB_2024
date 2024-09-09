#include "h_bridge.h" //inclui biblioteca local
#include "encoder.h"
#include "pid.h"
#include "pid_ctrl.h"

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

void testeEncoder(pcnt_unit_handle_t encoder){
    /* Loop para testa o encoder */
    while(1){
        //update_motor(MOTOR_RIGHT, maxRes);
        vTaskDelay(60 / portTICK_PERIOD_MS); 
        pulse_count(encoder); //qtde de pulso a cada 60ms
    }
}

void app_main() {
    init_gpio(MOTOR_RIGHT);
    init_pwm(MOTOR_RIGHT);

    pcnt_unit_handle_t encoderR = init_encoder(ENCODER_RIGHT);
    pcnt_unit_handle_t encoderL = init_encoder(ENCODER_LEFT);

    
    /*PID*/
    //Pseudo Código:
    /*
        error_prior = 0
        integral_prior = 0
        KP = ?
        KI = ?
        KD = ?
        bias = ? (evita que o output seja 0)

        while(1) {
            error = desired_value – actual_value
            integral = integral_prior + error * iteration_time
            derivative = (error – error_prior) / iteration_time
            output = KP*error + KI*integral + KD*derivative + bias
            error_prior = error
            integral_prior = integral
            sleep(iteration_time) (delay?)
        }
    */

   

}
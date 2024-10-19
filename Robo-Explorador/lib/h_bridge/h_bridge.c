/* Aqui: funções declaradas no .h */

#include "h_bridge.h"

/* Inicializa os pinos GPIO */
void init_gpio(type_side_motor motor){
    //gpio_set_direction(pino, tipo) para definir o tipo do pino (input/output)

    gpio_set_direction(PWM(motor), GPIO_MODE_OUTPUT); // pino pwm
    gpio_set_direction(pinPonteH_1(motor), GPIO_MODE_OUTPUT); // pino 1 para a ponte h
    gpio_set_direction(pinPonteH_2(motor), GPIO_MODE_OUTPUT); // pino 2 para a ponte h

    gpio_set_direction(pinStandBy, GPIO_MODE_OUTPUT); // stand by - sempre HIGH
    gpio_set_level(pinStandBy, HIGH);
}

/* Configura timer e canal PWM */
void init_pwm(type_side_motor motor){

    ledc_timer_config_t ledc_timer = { //estrutura para configurar os parâmetros do timer
        .speed_mode = LEDC_SPEED_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQ,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer); //função para configurar o timer

    ledc_channel_config_t channel_conf = { //estrutura para configurar os parâmetros do canal
        .gpio_num = PWM(motor),
        .speed_mode = LEDC_SPEED_MODE,
        .channel = LEDC_CHANNEL(motor),
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = 0   //set duty para 0%
    };
    ledc_channel_config(&channel_conf); //função para configurar um canal pwm
}

/* Seta a velocidade e direção do motor */
void update_motor(type_side_motor motor, float vel){
    // valor negativo e positivo de vel indicam direções diferentes
    if(vel >= 0){ 
        gpio_set_level(pinPonteH_1(motor), LOW);
        gpio_set_level(pinPonteH_2(motor), HIGH);
    }
    else{
        gpio_set_level(pinPonteH_1(motor), HIGH);
        gpio_set_level(pinPonteH_2(motor), LOW);
        vel = -vel;
    }
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, vel);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

// Função teste - aplica diferentes valores de PWM nas duas direções
void testePWM(type_side_motor motor){
    int maxRes = 1023; //valor do duty cycle em 100%
    int step = 100; // incremento do PWM

    /* Loop para testar o pwm */
    while(1){ 

        //DIREÇÃO 1
        for(int i=0; i<=maxRes; i+= step){    // varia de 0 a 1023
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        for(int i=maxRes; i>=0; i-= step){    // varia de 1023 a 0
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        //DIREÇÃO 2
        for(int i=0; i>=-maxRes; i-= step){   //varia de 0 a -1023
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        for(int i=-maxRes; i<=0; i+= step){   //varia de -1023 a 0
            update_motor(motor, i);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
#include "pwm_hbridge.h"

/*** Este programa utiliza a esp32 e uma ponte H para mover um motor a uma velocidade específica.***/

// <Passo 1> Inicialização dos parâmetros utilizados: gpios e pwm de cada motor

// inicializando os gpios
void init_gpio()
{
    //Definindo outputs do motor 1
    gpio_set_direction(INPUT_LEFT_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(INPUT_LEFT_2, GPIO_MODE_OUTPUT);
    //Definindo outputs do motor 2
    gpio_set_direction(INPUT_RIGHT_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(INPUT_RIGHT_2, GPIO_MODE_OUTPUT);
    //Definindo os enables para o motor 1 e 2
    gpio_set_direction(LEDC_OUTPUT_RIGHT, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDC_OUTPUT_LEFT, GPIO_MODE_OUTPUT);
}

//inicializando o pwm dos motores
void init_pwm()
{
    // configurando de forma geral o pwm tanto do motor 1 quanto do motor 2
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);
    
    // pwm do motor 1
    ledc_channel_config_t ledc_left_channel = {
        // definindo o que cada pino é responsável no motor 1
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_LEFT,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_LEFT,
        .duty = 0,
        .hpoint = 0,
    };
    ledc_channel_config(&ledc_left_channel);
    
    // pwm do motor 2
    ledc_channel_config_t ledc_right_channel = {
        // definindo o que cada pino é responsável no motor 2
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL_RIGHT,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT_RIGHT,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_right_channel);
}


/* <Passo 2> Definições das funções utilizadas para mover o motor.

        * u será a velocidade do motor, definida através do pwm.
        * A direção do motor é definida através de HIGH (1) ou LOW (0). 
        * esp_err_t checa se há erros na definição do sentido do motor.
*/


// define que input 1 == HIGH é sentido para frente, retorna ESP_OK se deu certo
esp_err_t _set_forward(motor_side_t motor) 
{   
    gpio_set_level(MOTOR_INPUT_1(motor), HIGH);
    gpio_set_level(MOTOR_INPUT_2(motor), LOW);
    return ESP_OK;
}

// define que input 2 == HIGH é sentido para trás, retorna ESP_OK se deu certo
esp_err_t _set_backward(motor_side_t motor) 
{   
    gpio_set_level(MOTOR_INPUT_1(motor), LOW);
    gpio_set_level(MOTOR_INPUT_2(motor), HIGH);
    return ESP_OK;
}


// escolhe um motor (1 ou 2) para andar com velocidade u. u>0 = sentido para frente, u<0 = sentido para trás.
esp_err_t update_motor(motor_side_t motor, int u) 
{  
    u > 0 ? _set_forward(motor) : _set_backward(motor);
    
// faz o movimento do motor com o u escolhido (frente/trás), retorna ESP_OK se deu certo
    u = abs(u);                                         // em módulo: pwm não aceita negativo
    ledc_set_duty(LEDC_MODE, MOTOR_CHANNEL(motor), u);  //set o sentido (sinal de u) e velocidade (valor de u)
    ledc_update_duty(LEDC_MODE, MOTOR_CHANNEL(motor));  //movimento do motor
    return ESP_OK; 
}


#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"


// definições dos gpios dos motores
#define INPUT_RIGHT_1   GPIO_NUM_2
#define INPUT_RIGHT_2   GPIO_NUM_4
#define INPUT_LEFT_1   GPIO_NUM_18
#define INPUT_LEFT_2   GPIO_NUM_19

// gpios dos enables
#define LEDC_OUTPUT_RIGHT   GPIO_NUM_20
#define LEDC_OUTPUT_LEFT   GPIO_NUM_21

// define os valores de LEFT e RIGHT
typedef enum{
    LEFT = 0,
    RIGHT = 1
    } motor_side_t;

//definições gerais do pwm
#define LEDC_MODE   LEDC_LOW_SPEED_MODE            //Definir o modo de operação
#define LEDC_TIMER   LEDC_TIMER_0                  // Selecionar o timer
#define LEDC_DUTY_RES   LEDC_TIMER_10_BIT          // Definir a resolução do duty   
#define LEDC_FREQUENCY   (5000)                    // Definir a frequência


// define os canais
#define LEDC_CHANNEL_LEFT   LEDC_CHANNEL_0   
#define LEDC_CHANNEL_RIGHT   LEDC_CHANNEL_1

//define a direção do motor
#define MOTOR_INPUT_1(MOTOR) MOTOR == (LEFT) ? INPUT_LEFT_1 : INPUT_RIGHT_1 
#define MOTOR_INPUT_2(MOTOR) MOTOR == (LEFT) ? INPUT_LEFT_2 : INPUT_RIGHT_2 
#define HIGH   1
#define LOW   0


#define MOTOR_CHANNEL(MOTOR) MOTOR == (LEFT) ? LEDC_CHANNEL_LEFT : LEDC_CHANNEL_RIGHT 

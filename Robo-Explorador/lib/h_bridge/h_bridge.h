/* Aqui: inclusão de bibliotecas, definição de constantes e declaração das funções */

#ifndef H_BRIDGE_H
#define H_BRIDGE_H

// Bibliotecas
#include "esp_err.h"
#include "driver/gpio.h" //Funcionamento do GPIO
#include "driver/ledc.h"
#include "esp_log.h"

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "esp_system.h"

#define HIGH 1  
#define LOW 0

typedef enum{
    MOTOR_RIGHT = 0,
    MOTOR_LEFT = 1,
} type_side_motor;

// Pino Stand by
#define pinStandBy GPIO_NUM_27

// Pinos Ponte H MOTOR RIGHT
#define pinPonteH_1R GPIO_NUM_25    
#define pinPonteH_2R  GPIO_NUM_26   

// Pinos Ponte H MOTOR LEFT 
#define pinPonteH_1L GPIO_NUM_12    
#define pinPonteH_2L  GPIO_NUM_14

#define pinPonteH_1(SIDE) (SIDE == MOTOR_RIGHT)? pinPonteH_1R : pinPonteH_1L
#define pinPonteH_2(SIDE) (SIDE == MOTOR_RIGHT)? pinPonteH_2R : pinPonteH_2L

//PWM config
#define PWM_R GPIO_NUM_33 // motor right
#define PWM_L GPIO_NUM_13 // motor left
#define PWM(SIDE) (SIDE == MOTOR_RIGHT)? PWM_R : PWM_L 

#define LEDC_SPEED_MODE LEDC_LOW_SPEED_MODE
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_DUTY_RES LEDC_TIMER_10_BIT   //seta resolução para 10 bits (0 - 1023)
#define LEDC_FREQ 5000    //freq de 5kHz

#define LEDC_CHANNEL_R LEDC_CHANNEL_0
#define LEDC_CHANNEL_L LEDC_CHANNEL_1
#define LEDC_CHANNEL(SIDE) (SIDE == MOTOR_RIGHT)? LEDC_CHANNEL_R : LEDC_CHANNEL_L

//Funções
void init_gpio(type_side_motor motor);
void init_pwm(type_side_motor motor);
void update_motor(type_side_motor motor, float vel);

void testePWM(type_side_motor motor)

#endif
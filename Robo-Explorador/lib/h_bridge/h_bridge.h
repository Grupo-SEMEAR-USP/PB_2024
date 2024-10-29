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

// ------------- Placa Beatriz ------------------
// Pino Stand by
#define pinStandBy GPIO_NUM_27

// Pinos Ponte H MOTOR RIGHT    / A
#define pinPonteH_1R GPIO_NUM_25    
#define pinPonteH_2R  GPIO_NUM_26   

// Pinos Ponte H MOTOR LEFT     / B
#define pinPonteH_1L GPIO_NUM_12    
#define pinPonteH_2L  GPIO_NUM_14

//PWM config
#define PWM_R GPIO_NUM_33 // motor right    / A
#define PWM_L GPIO_NUM_13 // motor left     / B

// ------------- Placa Guilherme ------------------
// // Pino Stand by
// #define pinStandBy GPIO_NUM_17

// // Pinos Ponte H MOTOR RIGHT    / 2
// #define pinPonteH_1R GPIO_NUM_4    
// #define pinPonteH_2R  GPIO_NUM_16   

// // Pinos Ponte H MOTOR LEFT     / 1
// #define pinPonteH_1L GPIO_NUM_5    
// #define pinPonteH_2L  GPIO_NUM_18

// //PWM config
// #define PWM_R GPIO_NUM_2 // motor right   / 2
// #define PWM_L GPIO_NUM_19 // motor left   / 1

#define PWM(SIDE) (SIDE == MOTOR_RIGHT)? PWM_R : PWM_L 
#define pinPonteH_1(SIDE) (SIDE == MOTOR_RIGHT)? pinPonteH_1R : pinPonteH_1L
#define pinPonteH_2(SIDE) (SIDE == MOTOR_RIGHT)? pinPonteH_2R : pinPonteH_2L

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

void testePWM(type_side_motor motor);

#endif
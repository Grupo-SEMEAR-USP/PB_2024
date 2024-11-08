#ifndef ENCODER_H
#define ENCODER_H

//Bibliotecas
#include "driver/pulse_cnt.h" //biblioteca pulse count para o encoder
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/pulse_cnt.h"
#include "driver/gpio.h"
#include "esp_sleep.h" 

typedef enum{
    ENCODER_RIGHT = 0,
    ENCODER_LEFT = 1,
} type_side_encoder;

// // ------------- Placa Luiz ------------------
// // Canais A e B do encoder da direita (R)   / A
// #define CHA_A_ENC_R 19
// #define CHA_B_ENC_R 21

// // Canais A e B do encoder da esquerda (L)   / B
// #define CHA_A_ENC_L 18 
// #define CHA_B_ENC_L 4

// ------------- Placa Ulisses ------------------
// Canais A e B do encoder da direita (R)   / A
#define CHA_A_ENC_R 33
#define CHA_B_ENC_R 35

// Canais A e B do encoder da esquerda (L)   / B
#define CHA_A_ENC_L 32 
#define CHA_B_ENC_L 34

// ------------- Placa Beatriz ------------------
// // Canais A e B do encoder da direita (R)   / A
// #define CHA_A_ENC_R 5
// #define CHA_B_ENC_R 21

// // Canais A e B do encoder da esquerda (L)   / B
// #define CHA_A_ENC_L 19 
// #define CHA_B_ENC_L 18

// ------------- Placa Guilherme ------------------
// // Canais A e B do encoder da direita (R)    / 2
// #define CHA_A_ENC_R 23
// #define CHA_B_ENC_R 34

// // Canais A e B do encoder da esquerda (L)   / 1
// #define CHA_A_ENC_L 25 
// #define CHA_B_ENC_L 33

#define ENCODER_CHA_A(SIDE) (SIDE == ENCODER_RIGHT)? CHA_A_ENC_R : CHA_A_ENC_L
#define ENCODER_CHA_B(SIDE) (SIDE == ENCODER_RIGHT)? CHA_B_ENC_R : CHA_B_ENC_L

// Limites do PCNT
#define PCNT_HIGH_LIMIT 1500
#define PCNT_LOW_LIMIT -1500

/* Funções */
pcnt_unit_handle_t init_encoder(type_side_encoder encoder);
bool pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx) ;
float pulse_count(pcnt_unit_handle_t encoder, type_side_encoder side);

#endif
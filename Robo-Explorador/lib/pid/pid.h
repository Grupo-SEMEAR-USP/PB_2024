#ifndef PID_H
#define PID_H

#include "pid_ctrl.h"
#include "encoder.h"
#include "h_bridge.h"
#include "esp_err.h"

// (Atualizar parâmetros)
#define KP_R 1
#define KI_R 0
#define KD_R 0
#define MAX_OUTPUT_R 1023 
#define MIN_OUTPUT_R -1023 
#define MAX_INTEGRAL_R 100000  //limita a range da soma dos erros (só importa se usar PID_CAL_TYPE_POSITIONAL)
#define MIN_INTEGRAL_R 0

#define KP_L 0.1
#define KI_L 0
#define KD_L 0
#define MAX_OUTPUT_L 2046
#define MIN_OUTPUT_L 0
#define MAX_INTEGRAL_L 100000 
#define MIN_INTEGRAL_L 0

#define kp(SIDE) (SIDE == MOTOR_RIGHT)? KP_R : KP_L
#define ki(SIDE) (SIDE == MOTOR_RIGHT)? KI_R : KI_L
#define kd(SIDE) (SIDE == MOTOR_RIGHT)? KD_R : KD_L
#define max_output(SIDE) (SIDE == MOTOR_RIGHT)? MAX_OUTPUT_R : MAX_OUTPUT_L
#define min_output(SIDE) (SIDE == MOTOR_RIGHT)? MIN_OUTPUT_R : MIN_OUTPUT_L
#define max_integral(SIDE) (SIDE == MOTOR_RIGHT)? MAX_INTEGRAL_R : MAX_INTEGRAL_L
#define min_integral(SIDE) (SIDE == MOTOR_RIGHT)? MIN_INTEGRAL_R : MIN_INTEGRAL_L

pid_ctrl_block_handle_t init_pid(type_side_motor motor);
esp_err_t pid_apply(float* val_incrementado, pid_ctrl_block_handle_t pid, type_side_motor motor, pcnt_unit_handle_t encoder, float target_vel);

#endif
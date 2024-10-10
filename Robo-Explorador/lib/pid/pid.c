#include "pid.h"

const char *TAG_PID = "Pid";

pid_ctrl_block_handle_t init_pid(type_side_motor motor){

    pid_ctrl_parameter_t pid_param = {
        .kp = kp(motor),
        .ki = ki(motor),
        .kd = kd(motor),
        .max_output = max_output(motor),
        .min_output = min_output(motor),
        .max_integral = max_integral(motor),
        .min_integral = min_integral(motor),
        .cal_type = PID_CAL_TYPE_INCREMENTAL //(ou incremental?)
    };

    pid_ctrl_config_t pid_config = {
        .init_param = pid_param
    };

    pid_ctrl_block_handle_t pid;

    ESP_ERROR_CHECK(pid_new_control_block(&pid_config, &pid)); //cria bloco pid e faz o update dos valores do pid_param
    
    return pid;
}

//limites do PWM
void limite_PWM(float *val, float target_vel){
    if(*val > 1023) *val = 1023;
    if(*val < 0 && target_vel >= 0) *val = 0; //se velocidade alvo for positiva
    else if(*val < -1023 && target_vel < 0) *val = -1023; //se for negativa
}

esp_err_t pid_apply(float* val_incrementado, pid_ctrl_block_handle_t pid, type_side_motor motor, pcnt_unit_handle_t encoder, float target_vel){
    
    type_side_encoder side = (motor == MOTOR_RIGHT)? ENCODER_RIGHT : ENCODER_LEFT; 

    float k = 1; // constante de conversão ticks x rpm 
    float vel_atual = (float)pulse_count(encoder, side) * k; //delay de 50ms

    float erro = target_vel - vel_atual;
    
    //calcula e aplica pid
    float result;
    ESP_ERROR_CHECK(pid_compute(pid, erro, &result));
    result *= (1/k);
    *val_incrementado += result;

    limite_PWM(val_incrementado, target_vel);
    update_motor(motor, *val_incrementado);
    
    //ESP_LOGI(TAG_PID, "Alvo: %f  Erro: %f  PID: %f\n", target_vel, erro, *val_incrementado);
    return ESP_OK;
}
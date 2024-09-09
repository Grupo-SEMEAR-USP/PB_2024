#include "pid.h"

void teste(){

    float error, result; //(inicializar)
    ESP_ERROR_CHECK(pid_compute(pid, error, &result)); //calcula o resultado do pid na variavel result

    ESP_ERROR_CHECK(pid_update_parameters(pid, &pid_param)); //atualiza valores (pid recebe os parametros de pid_param)

    ESP_ERROR_CHECK(pid_reset_ctrl_block(pid)); //reseta valores de erros e output anteriores
}

pid_ctrl_block_handle_t init_pid(type_side_motor motor){

    pid_ctrl_parameter_t pid_param = {
        .kp = kp(motor),
        .ki = ki(motor),
        .kd = kd(motor),
        .max_output = max_output(motor),
        .min_output = min_output(motor),
        .max_integral = max_integral(motor),
        .min_integral = min_integral(motor),
        .cal_type = PID_CAL_TYPE_POSITIONAL //(ou incremental?)
    };

    pid_ctrl_config_t pid_config = {
        .init_param = pid_param
    };

    pid_ctrl_block_handle_t pid;

    ESP_ERROR_CHECK(pid_new_control_block(&pid_config, &pid)); //cria bloco pid e faz o update dos valores do pid_param
    
    return pid;
}

esp_err_t apply_pid(pid_ctrl_block_handle_t pid, type_side_motor motor, pcnt_unit_handle_t encoder, float target_vel){
    
    //como vai ser aplicado o delay?
    
    float k; // constante de conversão ticks x rpm
    float vel_atual = pulse_count(encoder) * k;

    float erro = target_vel - vel_atual;

    //calcula e aplica pid
    float result;
    ESP_ERROR_CHECK(pid_compute(pid, erro, &result));
    update_motor(motor, result + VAL_BASE);

    return ESP_OK;
}
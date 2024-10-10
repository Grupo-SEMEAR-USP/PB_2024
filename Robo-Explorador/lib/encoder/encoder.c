/* Código para 1 encoder */

#include "utils.h"
#include "encoder.h"

const char *TAG_ENCODER = "Encoder";

// Inicializa o encoder
pcnt_unit_handle_t init_encoder(type_side_encoder encoder){ 

    pcnt_unit_handle_t selected_encoder = NULL;
    
    // Cria nova unidade de contagem de pulsos
    ESP_LOGI(TAG_ENCODER, "Install pcnt unit");
    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
    };
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &selected_encoder));

    // Configura o filtro de ruídos
    ESP_LOGI(TAG_ENCODER, "Set glitch filter");
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(selected_encoder, &filter_config));

    // Cria um canal dentro da unidade de contagem de pulsos
    ESP_LOGI(TAG_ENCODER, "Install pcnt channels");
    pcnt_chan_config_t chan_a_config = {                // Canal A
        .edge_gpio_num = ENCODER_CHA_A(encoder),
        .level_gpio_num = ENCODER_CHA_B(encoder),
    };
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_a_config, &pcnt_chan_a));
    
    pcnt_chan_config_t chan_b_config = {               // Canal B
        .edge_gpio_num = ENCODER_CHA_B(encoder),
        .level_gpio_num = ENCODER_CHA_A(encoder),
    };
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_b_config, &pcnt_chan_b));

    // Define ações de borda e de nível para os canais
    ESP_LOGI(TAG_ENCODER, "Set edge and level actions for pcnt channels");
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    // Habilita a unidade de contagem de pulsos
    ESP_LOGI(TAG_ENCODER, "Enable pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_enable(selected_encoder));
    
    // Limpa
    ESP_LOGI(TAG_ENCODER, "Clear pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_clear_count(selected_encoder));

    // Inicia a contagem
    ESP_LOGI(TAG_ENCODER, "Start pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_start(selected_encoder));

    return selected_encoder;
}

// Faz alguma coisa que eu não entendo e é provavelmente useless
bool pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx) {
    BaseType_t high_task_wakeup;
    QueueHandle_t queue = (QueueHandle_t)user_ctx;

    xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);

    return (high_task_wakeup == pdTRUE);
}


// ADAPTAR PARA DOIS MOTORES !!!

// Retorna a quantidade de pulsos lidos em um intervalo de tempo
float pulse_count(pcnt_unit_handle_t encoder, type_side_encoder side){
    int pulse_count = 0;
    pcnt_unit_clear_count(encoder); //zera o contador de pulsos
    vTaskDelay(50/portTICK_PERIOD_MS);

    ESP_ERROR_CHECK(pcnt_unit_get_count(encoder, &pulse_count)); //a variavel pulse_count recebe a leitura do encoder
    ESP_LOGI(TAG_ENCODER, "Pulse count: %d", pulse_count);

    pcnt_unit_clear_count(encoder); //zera o contador de pulsos

    //(side == 0) ? ENCODER_READ_R = pulse_count : ENCODER_READ_L = pulse_count;

    if(side == ENCODER_RIGHT) ENCODER_READ_R = pulse_count;
    else ENCODER_READ_L = pulse_count;

    return pulse_count;
}
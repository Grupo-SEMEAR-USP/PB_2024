#include "encoder.h"

// Este programa coleta os sinais de um encoder em um intervalo de tempo e permite a vizualição dos ticks

const char *TAG_ENCODER = "Encoder"; //Definição da TAG

pcnt_unit_handle_t init_encoder(encoder_side_t cha_encoder){ // Inicialização do encoder

    pcnt_unit_handle_t selected_encoder = NULL;

    // Definição da configuração da unidade com os limites máximos e mínimos de contagem dos encoders
    ESP_LOGI(TAG_ENCODER, "Install pcnt unit");
    pcnt_unit_config_t unit_config = {
        .high_limit = PCNT_HIGH_LIMIT,
        .low_limit = PCNT_LOW_LIMIT,
    };
    // Configuração do pcnt
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &selected_encoder)); 

    // Configura um filtro de glitch (ruídos) para a unidade de contagem de pulsos em nanosegundos.
    ESP_LOGI(TAG_ENCODER, "Set glitch filter");
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    // COnfiguração do glitch
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(selected_encoder, &filter_config));

    // Definição da configuração do canal a do encoder
    ESP_LOGI(TAG_ENCODER, "Install pcnt channels");
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = ENCODER_INPUT_A(cha_encoder), // Pino do canal a do encoder
        .level_gpio_num = ENCODER_INPUT_B(cha_encoder), // Pino do canal b do encoder
    };
    //Configuração do canal
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_a_config, &pcnt_chan_a));
    
    //Definição da configuração do canal b do encoder
    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = ENCODER_INPUT_B(cha_encoder), // Pino do canal b do encoder
        .level_gpio_num = ENCODER_INPUT_A(cha_encoder), // Pino do canal a do encoder
    };

    // Configuração do canal
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(selected_encoder, &chan_b_config, &pcnt_chan_b));

    //O unico parâmetro que controlamos é o pcnt_chan_a e pctn_chan_b definidos acima
    ESP_LOGI(TAG_ENCODER, "Set edge and level actions for pcnt channels");
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    ESP_LOGI(TAG_ENCODER, "Enable pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_enable(selected_encoder));
    
    ESP_LOGI(TAG_ENCODER, "Clear pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_clear_count(selected_encoder));

    ESP_LOGI(TAG_ENCODER, "Start pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_start(selected_encoder));

    return selected_encoder;
}

// Função que retorna um valor booleano (True ou False)
bool pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx) {
    BaseType_t high_task_wakeup;
    QueueHandle_t queue = (QueueHandle_t)user_ctx;

    xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);

    return (high_task_wakeup == pdTRUE);
}


// Pulse Count - Função que retorna um valor float
float pulse_count(pcnt_unit_handle_t encoder){
    int pulse_count = 0;

    ESP_ERROR_CHECK(pcnt_unit_get_count(encoder, &pulse_count));
    ESP_LOGI(TAG_ENCODER, "Pulse count: %d", pulse_count);

    pcnt_unit_clear_count(encoder);

    return pulse_count;
}
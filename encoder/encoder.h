#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/pulse_cnt.h"
#include "driver/gpio.h"
#include "esp_sleep.h"

/* PCNT Limits */
#define PCNT_HIGH_LIMIT 1500
#define PCNT_LOW_LIMIT  -1500

/* Right encoder defines */
#define CHA_ENCODER_1R 18
#define CHA_ENCODER_2R 19

/* Left encoder defines */
#define CHA_ENCODER_1L 18
#define CHA_ENCODER_2L 19

/* Enum */
typedef enum {
    ENC_LEFT = 0,
    ENC_RIGHT = 1
} encoder_side_t;
    
/* Macro functions */
#define ENCODER_INPUT_A(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_1R : CHA_ENCODER_1L
#define ENCODER_INPUT_B(NUM) NUM == (ENC_RIGHT) ? CHA_ENCODER_2R : CHA_ENCODER_2L

pcnt_unit_handle_t init_encoder(encoder_side_t cha_encoder);
float pulse_count(pcnt_unit_handle_t encoder);
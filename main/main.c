#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "amy.h"

typedef enum {
    WAVE_SINE = 0,
    WAVE_TRIANGLE,
    WAVE_SAWTOOTH,
    WAVE_SQUARE,
    WAVE_MAX
} wave_type_t;

static const int amy_waves[WAVE_MAX] = {
    SINE, TRIANGLE, SAW_DOWN, PULSE,
};

static const char *wave_names[WAVE_MAX] = {
    "SINE",
    "TRIANGLE",
    "SAWTOOTH",
    "SQUARE (pulse)",
};

static const float melody[] = {
    261.63f, 329.63f, 392.00f, 493.88f, 523.25f,
    220.00f, 261.63f, 329.63f, 392.00f, 440.00f,
    174.61f, 220.00f, 261.63f, 329.63f, 349.23f,
    196.00f, 246.94f, 293.66f, 349.23f, 392.00f,
};

static void play_note(float freq, int wave) {
    char msg[48];
    if (wave == PULSE) {
        snprintf(msg, sizeof(msg), "v0w%df%gl1d0.5Z", wave, freq);
    } else {
        snprintf(msg, sizeof(msg), "v0w%df%gl1Z", wave, freq);
    }
    amy_play_message(msg);
}

void app_main(void) {
    amy_config_t config = amy_default_config();
    config.audio = AMY_AUDIO_IS_I2S;
    config.i2s_bclk = 4;
    config.i2s_lrc = 5;
    config.i2s_dout = 6;

    amy_start(config);

    const int num_notes = sizeof(melody) / sizeof(melody[0]);
    const int note_ms = 180;
    wave_type_t current_wave = WAVE_SINE;

    printf("\n=== AMY MELODY DEMO ===\n");
    printf("Playing: %s\n", wave_names[current_wave]);

    while (1) {
        for (int note_idx = 0; note_idx < num_notes; note_idx++) {
            play_note(melody[note_idx], amy_waves[current_wave]);
            vTaskDelay(pdMS_TO_TICKS(note_ms));
        }

        current_wave = (current_wave + 1) % WAVE_MAX;
        printf("Playing: %s\n", wave_names[current_wave]);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matrix.pio.h"

#define NUM_PIXELS 25
#define OUT_PIN 7
#define DEBOUNCE_TIME_MS 200

const uint button_B = 6; // Botão B - GPIO6
const uint button_A = 5; // Botão A - GPIO5

// Função para converter RGB normalizado em valor de 32 bits
uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Função que envia os dados da matriz para o PIO
void desenho_pio(const double *desenho, PIO pio, uint sm, double r, double g, double b) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[NUM_PIXELS - 1 - i] * b, desenho[NUM_PIXELS - 1 - i] * r, desenho[NUM_PIXELS - 1 - i] * g);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Frames da animação do botão B (coração)
const double frames_b[6][NUM_PIXELS] = {
    {
        0,0,0,0,0,
        0,0,1,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,1,0,1,0,
        0,0,1,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,1,0,1,0,
        1,0,1,0,1,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,1,0,1,0,
        1,0,1,0,1,
        1,0,0,0,1,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,1,0,1,0,
        1,0,1,0,1,
        1,0,0,0,1,
        0,1,0,1,0,
        0,0,0,0,0
    },
    {
        0,1,0,1,0,
        1,0,1,0,1,
        1,0,0,0,1,
        0,1,0,1,0,
        0,0,1,0,0
    }
};

// Frames da animação do botão A (fogos)
const double frames_a[5][NUM_PIXELS] = {
    {
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,1,0,0,
        0,0,0,0,0,
        0,0,0,0,0
    },
    {
        0,0,1,0,0,
        0,0,1,0,0,
        1,1,1,1,1,
        0,0,1,0,0,
        0,0,1,0,0
    },
    {
        0,1,0.5,1,0,
        1,0.5,1,0.5,1,
        0.5,1,1,1,0.5,
        1,0.5,1,0.5,1,
        0,1,0.5,1,0
    },
    {
        0,0.5,0.3,0.5,0,
        0.5,0.3,0.5,0.3,0.5,
        0.3,0.5,0.5,0.5,0.3,
        0.5,0.3,0.5,0.3,0.5,
        0,0.5,0.3,0.5,0
    },
    {
        0,0.2,0.1,0.2,0,
        0.2,0.1,0.2,0.1,0.2,
        0.1,0.2,0.2,0.2,0.1,
        0.2,0.1,0.2,0.1,0.2,
        0,0.2,0.1,0.2,0
    }
};

// Função para executar a animação do botão B
void animacao_botao_B(PIO pio, uint sm) {
    for (int f = 0; f < 6; f++) {
        desenho_pio(frames_b[f], pio, sm, 1.0, 0.0, 0.0); // vermelho
        sleep_ms(300);
    }
}

// Função para executar a animação do botão A
void animacao_botao_A(PIO pio, uint sm) {
    for (int f = 0; f < 5; f++) {
        desenho_pio(frames_a[f], pio, sm, 1.0, 1.0, 0.0); // amarelo
        sleep_ms(300);
    }
}

int main() {
    PIO pio = pio0;
    bool ok = set_sys_clock_khz(128000, false);
    stdio_init_all();

    printf("Iniciando a transmissão PIO\n");
    if (ok) printf("Clock set to %ld\n", clock_get_hz(clk_sys));

    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);

    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);

    absolute_time_t last_A = get_absolute_time();
    absolute_time_t last_B = get_absolute_time();

    while (true) {
        absolute_time_t now = get_absolute_time();

        if (!gpio_get(button_A) && absolute_time_diff_us(last_A, now) > DEBOUNCE_TIME_MS * 1000) {
            animacao_botao_A(pio, sm);
            last_A = now;
        } else if (!gpio_get(button_B) && absolute_time_diff_us(last_B, now) > DEBOUNCE_TIME_MS * 1000) {
            animacao_botao_B(pio, sm);
            last_B = now;
        }

        sleep_ms(10);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matrix.pio.h"

#define NUM_PIXELS 25
#define OUT_PIN 7

const uint button_B = 6; // Botão 1 - GPIO6
const uint button_A = 5; // Botão 2 - GPIO5

uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
    for (int i = 0; i < NUM_PIXELS; i++) {
        if (i % 2 == 0)
            valor_led = matrix_rgb(desenho[24 - i], r, g);
        else
            valor_led = matrix_rgb(0.0, desenho[24 - i], g);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Espaço reservado para a Animação do Botão B (GPIO 6)
void animacao_botao_1(PIO pio, uint sm) {
    // Dona laísa - Adicione sua animação aqui
}

// Espaço reservado para a Animação do Botão A (GPIO 5)
void animacao_botao_2(PIO pio, uint sm) {
    // Dona laíse - Adicione sua animação aqui
}

int main()
{
    PIO pio = pio0;
    bool ok;
    uint32_t valor_led;
    double r = 1.0, g = 0.0, b = 0.0;

    ok = set_sys_clock_khz(128000, false);
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

    while (true) {
        if (!gpio_get(button_A)) {
            animacao_botao_A(pio, sm); // Executa a animação do botão 2
        }
        else if (!gpio_get(button_B)) {
            animacao_botao_B(pio, sm); // Executa a animação do botão 1
        }

        sleep_ms(300);
    }
}

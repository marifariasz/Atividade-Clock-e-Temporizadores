#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define GREEN_LED 11   // LED verde (BitDogLab - vermelho)
#define YELLOW_LED 12  // LED amarelo (BitDogLab - azul)
#define RED_LED 13     // LED vermelho (BitDogLab - verde)

// Estados do semáforo
int estado_atual = 1;
int estado_semaforo = 1;

// Intervalos de tempo (em milissegundos)
const int TEMPO_LED = 3000;
const int TEMPO_PRINT = 1000;

// Função para inicializar os LEDs
void iniciar_leds() {
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_init(YELLOW_LED);
    gpio_set_dir(YELLOW_LED, GPIO_OUT);
}

// Função para definir o estado dos LEDs
void set_led_state(bool red, bool yellow, bool green) {
    gpio_put(RED_LED, red);
    gpio_put(YELLOW_LED, yellow);
    gpio_put(GREEN_LED, green);
}

// Atualiza o estado do semáforo (LEDs)
void atualizar_estado_leds() {
    switch (estado_atual) {
        case 1: set_led_state(0, 0, 1); break; // Verde
        case 2: set_led_state(0, 1, 0); break; // Amarelo
        case 3: set_led_state(1, 0, 0); break; // Vermelho
    }
}

// Exibe a contagem regressiva do semáforo
void imprimir_estado_semaforo() {
    const char *mensagens[] = {
        "RED 3", "RED 2", "RED 1",
        "YELLOW 3", "YELLOW 2", "YELLOW 1",
        "GREEN 3", "GREEN 2", "GREEN 1"
    };
    printf("%s\n", mensagens[estado_semaforo - 1]);
}

// Callback do temporizador para alternar LEDs
bool callback_timer_leds(struct repeating_timer *t) {
    estado_atual = (estado_atual % 3) + 1;
    atualizar_estado_leds();
    return true;
}

// Callback do temporizador para exibir mensagens
bool callback_timer_mensagens(struct repeating_timer *t) {
    estado_semaforo = (estado_semaforo % 9) + 1;
    imprimir_estado_semaforo();
    return true;
}

int main() {
    stdio_init_all();  // Inicializa comunicação serial
    iniciar_leds();    // Configura os pinos dos LEDs
    atualizar_estado_leds();
    imprimir_estado_semaforo();

    struct repeating_timer timer_leds, timer_mensagens;

    // Configuração dos temporizadores
    add_repeating_timer_ms(TEMPO_LED, callback_timer_leds, NULL, &timer_leds);
    add_repeating_timer_ms(TEMPO_PRINT, callback_timer_mensagens, NULL, &timer_mensagens);

    while (1) {
        // Loop infinito para manter o programa rodando
    }

    return 0;
}
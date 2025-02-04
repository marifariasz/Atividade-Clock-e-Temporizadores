#include <stdio.h>
#include "pico/stdlib.h"     // Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define green 11    // Definindo o led verde no pino 11 (vermelho da bitDogLab)
#define yellow 12  // Definindo o led amarelo no pino 12 (azul da bitDogLab)
#define red 13    //Definindo o led vermelho no pino 13 (Verde da BitDogLab)
#define button 5  // Botão no pino 5

int estado_leds = 0; // Estado atual dos LEDs (0 = desligado, 1 = todos ligados, 2 = dois ligados, 3 = um ligado, 4 = todos ligados por 1 segundo)
bool botao_bloqueado = false; // Variável para bloquear o botão durante a execução

// Inicializando leds e botão
void iniciar() {
  gpio_init(red); gpio_set_dir(red, GPIO_OUT);         //led vermelho
  gpio_init(green); gpio_set_dir(green, GPIO_OUT);    // led verde
  gpio_init(yellow); gpio_set_dir(yellow, GPIO_OUT); // led amarelo
  gpio_init(button); gpio_set_dir(button, GPIO_IN); // botão
  gpio_pull_up(button); // Habilita pull-up no botão
}

// Função para ligar os leds com uma linha de código
void state(bool r, bool y, bool g) {
  gpio_put(red, r);
  gpio_put(green, g);
  gpio_put(yellow, y);
}

// Função de callback para o alarme
int64_t alarm_callback(alarm_id_t id, void *user_data) {
    switch (estado_leds) {
        case 1:
            // Após 3 segundos, liga dois LEDs
            state(1, 1, 0); // Vermelho e amarelo ligados
            estado_leds = 2;
            add_alarm_in_ms(3000, alarm_callback, NULL, false); // Configura novo alarme
            printf("\nAzul Desligado");
            break;
        case 2:
            // Após mais 3 segundos, liga um LED
            state(1, 0, 0); // Apenas vermelho ligado
            estado_leds = 3;
            add_alarm_in_ms(3000, alarm_callback, NULL, false); // Configura novo alarme
            printf("\nvermelho e azul desligado");
            break;
        case 3:
            // Após mais 3 segundos, liga todos os LEDs por 1 segundo
            state(0, 0, 0); // Todos os LEDs ligados
            estado_leds = 4;
            add_alarm_in_ms(1000, alarm_callback, NULL, false); // Configura novo alarme para 1 segundo
            printf("\nTodos os LEDs desligados");
            break;
        case 4:
            // Após 1 segundo, desliga todos os LEDs e libera o botão
            state(0, 0, 0); // Todos desligados
            estado_leds = 0;
            botao_bloqueado = false; // Libera o botão
            printf("\n\nBotao liberado!!");
            break;
    }
    return 0; // Retorna 0 para indicar que o alarme não deve ser repetido
}

// Função principal
int main() {
    iniciar();           // Habilitar os pinos dos leds e botão
    stdio_init_all();   // Habilita o monitor serial

    // Loop infinito que mantém o programa em execução.
    while (1) {
        // Verifica se o botão foi pressionado e se não está bloqueado
        if (!gpio_get(button) && !botao_bloqueado) {
            botao_bloqueado = true; // Bloqueia o botão
            estado_leds = 1; // Define o estado inicial dos LEDs
            state(1, 1, 1); // Liga todos os LEDs
            printf("\nINICIA ROTINA\nTODOS LEDS LIGADOS");
            add_alarm_in_ms(3000, alarm_callback, NULL, false); // Configura o primeiro alarme
            sleep_ms(300); // Debounce do botão
        }
        sleep_ms(10); // Pequena pausa para evitar leitura excessiva do botão
    }
    return 0;
}
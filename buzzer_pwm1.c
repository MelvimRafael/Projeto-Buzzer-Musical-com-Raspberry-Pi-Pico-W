#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUZZER_PIN 21
#define BUTTON_A 5
#define BUTTON_B 6

// Escala de Dó
const uint scale_notes[] = {262, 294, 330, 349, 392, 440, 494, 523};  
const uint scale_duration[] = {500, 500, 500, 500, 500, 500, 500, 500}; 

// Parabéns pra Você 
const uint parabens_notes[] = {523, 523, 587, 523, 698, 659, 523, 523, 587, 523, 784, 698, 523, 523, 880, 698, 659, 587, 698, 698, 659, 698, 523, 523};
const uint parabens_duration[] = {500, 250, 500, 500, 500, 1000, 500, 250, 500, 500, 500, 1000, 500, 250, 500, 500, 500, 500, 1000, 500, 250, 500, 500};

// Inicializa o buzzer com PWM
void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    
    
    pwm_config_set_clkdiv(&config, 4.0f);  
    pwm_set_gpio_level(pin, 0);  
}

// Função para reproduzir uma nota com frequência e duração específicas
void play_tone(uint pin, uint frequency, uint duration_ms) {
    if (frequency == 0) {
        sleep_ms(duration_ms);
        return;
    }

    // Limita a frequência para o intervalo suportado pelo buzzer (aproximadamente 262 Hz a 880 Hz)
    if (frequency < 262) {
        frequency = 262;  // Limite inferior (Dó médio)
    }
    if (frequency > 880) {
        frequency = 880; // Limite superior (Lá médio)
    }

    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t top = clock_freq / (frequency * 8) - 1;  

    pwm_set_wrap(slice_num, top);  
    pwm_set_gpio_level(pin, top / 2); 

    sleep_ms(duration_ms);  // Toca a nota por um tempo adequado
    pwm_set_gpio_level(pin, 0);  // Desliga o buzzer após a duração
    sleep_ms(50);  // Pausa entre as notas
}

// Função para reproduzir uma música
void play_music(const uint *notes, const uint *durations, int length) {
    for (int i = 0; i < length; i++) {
        play_tone(BUZZER_PIN, notes[i], durations[i]);
    }
}

int main() {
    stdio_init_all();
    pwm_init_buzzer(BUZZER_PIN);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    while (1) {
        if (gpio_get(BUTTON_A) == 0) {
            sleep_ms(200);  // Debounce do botão
            play_music(scale_notes, scale_duration, sizeof(scale_notes) / sizeof(scale_notes[0]));
        }

        if (gpio_get(BUTTON_B) == 0) {
            sleep_ms(200);  // Debounce do botão
            play_music(parabens_notes, parabens_duration, sizeof(parabens_notes) / sizeof(parabens_notes[0]));
        }

        sleep_ms(10);  // Pausa para evitar sobrecarga do loop
    }

    return 0;
}

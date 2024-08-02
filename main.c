/* 
    This code originates from the Getting started with Raspberry Pi Pico document
    https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
    CC BY-ND Raspberry Pi (Trading) Ltd
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/pwm.h"

uint32_t pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d) {
    uint32_t clock = 125000000;
    uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) !=0);
    if (divider16 / 16 == 0) {
        divider16 = 16;
    }
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap*d/100);
    return wrap;
}

const uint LED_PIN = 20;
#define PWM_FREQ 50


int main() {
    bi_decl(bi_program_description("PROJECT DESCRIPTION"));
    puts("Hello, world!");


    // gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    // uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    // uint chan = pwm_gpio_to_channel(LED_PIN);
    // pwm_set_freq_duty(slice_num, chan, PWM_FREQ, 5);
    // pwm_set_enabled(slice_num, true);

    // int counter = 0;
    // while (1) {
    //     counter = (counter + 1) % 101;
    //     pwm_set_freq_duty(slice_num, chan, PWM_FREQ, counter);
    //     sleep_ms(50);
    //     printf("Counter: %d\n", counter);
    // }
}
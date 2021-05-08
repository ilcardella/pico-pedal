#include "audio_pwm.h"

AudioPwm::AudioPwm(const uint &p0, const uint &p1) : pwm0(p0), pwm1(p1)
{
    gpio_set_function(pwm0, GPIO_FUNC_PWM);
    gpio_set_function(pwm1, GPIO_FUNC_PWM);

    // Calculate the divider to get a 9.6Mhz PWM output
    uint32_t divider = 2;

    // Configure the PWM
    config = pwm_get_default_config();
    // Set clock divider
    pwm_config_set_clkdiv_int(&config, divider);
    // Both channels use 6 bits: 2^6=64
    pwm_config_set_wrap(&config, 64);

    // Start the channels
    pwm_init(pwm_gpio_to_slice_num(pwm0), &config, true);
    pwm_init(pwm_gpio_to_slice_num(pwm1), &config, true);

    pwm_set_gpio_level(pwm0, 0);
    pwm_set_gpio_level(pwm1, 0);
}

void AudioPwm::send(const uint32_t &signal)
{
    pwm_set_gpio_level(pwm1, signal & 0x3F);
    pwm_set_gpio_level(pwm0, signal >> 6);
}

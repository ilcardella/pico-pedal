#include "audio_pwm.h"

#include "hardware/pwm.h"

AudioPwm::AudioPwm(const uint &pwm1, const uint &pwm2) : pwm1(pwm1), pwm2(pwm2)
{
    gpio_set_function(pwm1, GPIO_FUNC_PWM);
    gpio_set_function(pwm2, GPIO_FUNC_PWM);

    // Configure the PWM with the minimum divider (clk_sys / 2)
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv_int(&config, 2);
    // Both channels use 6 bits
    pwm_config_set_wrap(&config, 64);

    // Start the channels
    pwm_init(pwm_gpio_to_slice_num(pwm1), &config, true);
    pwm_init(pwm_gpio_to_slice_num(pwm2), &config, true);
}

void AudioPwm::send(const uint32_t &signal)
{
    pwm_set_gpio_level(pwm1, signal & 0x3F);
    pwm_set_gpio_level(pwm2, signal >> 6);
}

#include "audio_pwm.h"

AudioPwm::AudioPwm(const uint &pwm1, const uint &pwm2) : pwm1(pwm1), pwm2(pwm2)
{
    gpio_set_function(pwm1, GPIO_FUNC_PWM);
    gpio_set_function(pwm2, GPIO_FUNC_PWM);

    // Configure the PWM
    config = pwm_get_default_config();
    // TODO: This might not be necessary and we could use a smaller divider like 2
    pwm_config_set_clkdiv_int(&config, 14); // 133Mhz / 14 = 9.6Mhz
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

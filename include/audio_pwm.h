#pragma once

#include <hardware/pwm.h>
#include <pico/stdlib.h>

class AudioPwm
{
  public:
    AudioPwm(const uint &pwm1, const uint &pwm2);
    ~AudioPwm() = default;

    void send(const uint32_t &signal);

  private:
    uint pwm1;
    uint pwm2;
    pwm_config config;
};

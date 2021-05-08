#pragma once

#include <hardware/pwm.h>
#include <pico/stdlib.h>

class AudioPwm
{
  public:
    AudioPwm(const uint &p0, const uint &p1);
    ~AudioPwm() = default;

    void send(const uint32_t &signal);

  private:
    uint pwm0;
    uint pwm1;
    pwm_config config;
};

#pragma once

#include <pico/stdlib.h>

class Potentiometer
{
  public:
    Potentiometer(const uint &p, const uint &ch);
    ~Potentiometer() = default;

    float get_percent_value();

  private:
    static constexpr int ADC_VALUES = 4096;
    uint pin;
    uint channel;
};

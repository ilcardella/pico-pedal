#pragma once

#include <pico/stdlib.h>

class Potentiometer
{
  public:
    Potentiometer(const uint &p, const uint &ch);
    ~Potentiometer() = default;

    float get_percent_value();

  private:
    uint pin;
    uint channel;
};

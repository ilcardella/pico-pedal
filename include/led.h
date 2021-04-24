#pragma once

#include <pico/stdlib.h>

class Led
{
  public:
    Led(const uint &pin);
    ~Led() = default;

    void on();
    void off();
    void set(const bool &enable);

  private:
    uint pin;
};

#pragma once

#include <pico/stdlib.h>

class Switch
{
  public:
    Switch(const uint &pin);
    ~Switch() = default;

    bool is_on();
    bool is_off();

  private:
    uint pin;
};

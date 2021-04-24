#pragma once

#include <pico/stdlib.h>

class Button
{
  public:
    Button(const uint &pin);
    ~Button() = default;

    bool is_pressed_and_released();

  private:
    bool get_state();

    uint pin;
    bool state = false;
};

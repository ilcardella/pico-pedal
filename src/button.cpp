#include "button.h"

Button::Button(const uint &pin) : pin(pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
    state = gpio_get(pin);
}

bool Button::is_pressed_and_released()
{
    bool value = gpio_get(pin);
    if (value != state)
    {
        state = value;
        if (state)
        {
            return true;
        }
    }
    return false;
}

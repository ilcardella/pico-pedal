#include "button.h"

Button::Button(const uint &pin) : pin(pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
    state = get_state();
}

bool Button::is_pressed_and_released()
{
    // TODO handle debouncing
    bool value = get_state();
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

bool Button::get_state()
{
    // High = button not pressed
    return not gpio_get(pin);
}

#include "switch.h"

Switch::Switch(const uint &pin) : pin(pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

bool Switch::is_on()
{
    return gpio_get(pin);
}

bool Switch::is_off()
{
    return not is_on();
}

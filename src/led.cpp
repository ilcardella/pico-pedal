#include "led.h"

Led::Led(const uint &p) : pin(p)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void Led::on()
{
    gpio_put(pin, 1);
}

void Led::off()
{
    gpio_put(pin, 0);
}

void Led::set(const bool &enable)
{
    enable ? on() : off();
}

#include "potentiometer.h"

#include "hardware/adc.h"

Potentiometer::Potentiometer(const uint &p, const uint &ch) : pin(p), channel(ch)
{
    adc_init();
    adc_gpio_init(pin);
    adc_select_input(channel);
}

float Potentiometer::get_percent_value()
{
    uint16_t result = adc_read();

    return static_cast<float>(result * 100 / 4096);
}

#include "display.h"

#include <hardware/i2c.h>

#include "ssd1306/logo.hpp"

Display::Display(const uint &sda, const uint &scl)
{
    i2c_init(i2c0, 400 * 1000); // 400KHz
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);

    oled = std::make_unique<GFX>(0x3C, 128, 64, i2c0);
    oled->display(logo);
    start_time = to_ms_since_boot(get_absolute_time());
}

void Display::set_fx_name(const std::string &value)
{
    fx_name = value;
}

void Display::set_message(const std::string &value)
{
    message = value;
}

void Display::show()
{
    auto now = to_ms_since_boot(get_absolute_time());
    if (now - previous_update_time >= REFRESH_PERIOD and (not is_logo_time(now)))
    {
        oled->clear();
        // TODO Make it pretty
        oled->drawString(1, 1, fx_name);
        oled->drawString(1, 50, message);
        oled->display();
        previous_update_time = now;
    }
}

bool Display::is_logo_time(const unsigned long &ts)
{
    return (ts - start_time) < LOGO_TIME;
}

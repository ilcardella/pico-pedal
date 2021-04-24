#include "display.h"

#include "ssd1306/logo.hpp"

Display::Display(const uint &sda, const uint &scl, i2c_inst_t *bus)
    : i2c_bus(bus), buffer()
{
    i2c_init(i2c_bus, I2C_FREQ);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);

    oled = std::make_unique<GFX>(0x3C, 128, 64, i2c_bus);
    oled->display(logo);
    start_time = to_ms_since_boot(get_absolute_time());
}

void Display::set_fx_name(const std::string &value)
{
    buffer.fx_name = value;
}

void Display::set_message(const std::string &value)
{
    buffer.message = value;
}

void Display::set_gain_percent(const float &value)
{
    buffer.gain_percent = static_cast<unsigned int>(value * 100);
}

void Display::set_fx_enabled(const bool &enabled)
{
    buffer.fx_enabled = enabled;
}

void Display::set_toggle_status(const bool &enabled)
{
    buffer.toggle_on = enabled;
}

void Display::show()
{
    auto now = to_ms_since_boot(get_absolute_time());
    if (now - previous_update_time >= REFRESH_PERIOD and (not is_logo_time(now)))
    {
        oled->clear();
        // TODO Make it pretty
        oled->drawString(1, 1, buffer.fx_name);
        oled->drawString(1, 12, std::to_string(buffer.gain_percent));
        oled->drawString(1, 24, std::to_string(buffer.fx_enabled));
        oled->drawString(1, 36, std::to_string(buffer.toggle_on));
        oled->drawString(1, 50, buffer.message);
        oled->display();
        previous_update_time = now;
    }
}

bool Display::is_logo_time(const unsigned long &ts)
{
    return (ts - start_time) < LOGO_TIME;
}

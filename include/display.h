#pragma once

#include <memory>
#include <string>

#include <hardware/i2c.h>

#include <pico/stdlib.h>

#include "ssd1306/GFX.hpp"

class Display
{
  public:
    Display(const uint &sda, const uint &scl, i2c_inst_t *bus);
    ~Display() = default;

    void set_fx_name(const std::string &value);
    void set_message(const std::string &value);
    void show();

  private:
    bool is_logo_time(const unsigned long &ts);

    std::unique_ptr<GFX> oled;
    i2c_inst_t *i2c_bus;

    static constexpr unsigned long REFRESH_PERIOD = 100; // ms
    static constexpr unsigned long LOGO_TIME = 2000;     // ms
    static constexpr unsigned long I2C_FREQ = 400000;    // Hz
    unsigned long start_time = 0;
    unsigned long previous_update_time = 0;
    std::string message = "Standby";
    std::string fx_name = "Unknown";
};

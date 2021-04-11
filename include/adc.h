#pragma once

#include <array>

#include <pico/stdlib.h>

class Adc
{
  public:
    Adc(const uint &clk, const uint &cs, const uint &miso, const uint &mosi);
    ~Adc() = default;

    uint32_t read();

  private:
    uint clk_pin;
    uint cs_pin;
    uint miso_pin;
    uint mosi_pin;

    // 12 bit ADC read channel 0
    static constexpr std::array<uint8_t, 3> CHANNEL_0_REQ = {0x01, 0x00, 0x00};
};

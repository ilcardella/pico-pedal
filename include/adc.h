#pragma once

#include <array>

#include <hardware/spi.h>
#include <pico/stdlib.h>

class Adc
{
  public:
    static constexpr unsigned int ADC_MIN = 0;
    static constexpr unsigned int ADC_MAX = 4095;

    Adc(const uint &clk, const uint &cs, const uint &miso, const uint &mosi,
        spi_inst_t *bus);
    ~Adc() = default;

    uint32_t read();

  private:
    // 12 bit ADC read channel 0
    static constexpr std::array<uint8_t, 3> CHANNEL_0_REQ = {0x01, 0x00, 0x00};
    // TODO is this too high? Maybe 0.9Mhz?
    static constexpr unsigned int SPI_FREQ = 900000; // Hz

    uint clk_pin;
    uint cs_pin;
    uint miso_pin;
    uint mosi_pin;
    spi_inst_t *spi_bus;
};

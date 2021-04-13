#include "adc.h"

#include "hardware/spi.h"

static inline void cs_select(const uint &cs)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(cs, 0);
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect(const uint &cs)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(cs, 1);
    asm volatile("nop \n nop \n nop");
}

Adc::Adc(const uint &clk, const uint &cs, const uint &miso, const uint &mosi)
    : clk_pin(clk), cs_pin(cs), miso_pin(miso), mosi_pin(mosi)
{
    spi_init(spi0, 4 * 1000 * 1000); // 4Mhz
    gpio_set_function(clk_pin, GPIO_FUNC_SPI);
    gpio_set_function(miso_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);

    // CS pin is manually managed and initialised to HIGH
    gpio_init(cs_pin);
    gpio_set_dir(cs_pin, GPIO_OUT);
    gpio_put(cs_pin, 1);
}

uint32_t Adc::read()
{
    uint32_t signal(0);
    std::array<uint8_t, 3> miso_buffer = {0};

    // Set CS pin LOW to notify comms are starting
    cs_select(cs_pin);

    // Read 3 bytes from the ADC
    spi_write_read_blocking(spi0, CHANNEL_0_REQ.data(), miso_buffer.data(), 3);

    // Set CS pin HIGH to notify comms are ending
    cs_deselect(cs_pin);

    // Extract the value
    signal = miso_buffer[2] + ((miso_buffer[1] & 0x0F) << 8);

    return signal;
}

#pragma once

#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>

#include <guitar_fx_lib/fx_manager.hpp>

#include "adc.h"
#include "audio_pwm.h"
#include "button.h"
#include "display.h"
#include "led.h"
#include "potentiometer.h"
#include "switch.h"

class PicoPedal
{
  public:
    PicoPedal();
    ~PicoPedal() = default;

    void spin();

  private:
    static constexpr uint PWM_OUT_1_PIN = 22;
    static constexpr uint PWM_OUT_2_PIN = 21;
    static constexpr uint BUTTON_BACK_PIN = 10;
    static constexpr uint BUTTON_NEXT_PIN = 11;
    static constexpr uint DISPLAY_I2C_SDA = 2;
    static constexpr uint DISPLAY_I2C_SCL = 3;
    static constexpr i2c_inst_t *I2C_BUS = i2c1;
    static constexpr uint LED_PIN = PICO_DEFAULT_LED_PIN; // 6;
    static constexpr uint POTENTIOMETER_PIN = 26;
    static constexpr uint POTENTIOMETER_CH = 0;
    static constexpr uint TOGGLE_PIN = 7;
    static constexpr uint FOOT_SWITCH_PIN = 8;
    static constexpr uint ADC_SPI_SCK_PIN = PICO_DEFAULT_SPI_SCK_PIN;
    static constexpr uint ADC_SPI_CS_PIN = PICO_DEFAULT_SPI_CSN_PIN;
    static constexpr uint ADC_SPI_MISO_PIN = PICO_DEFAULT_SPI_RX_PIN;
    static constexpr uint ADC_SPI_MOSI_PIN = PICO_DEFAULT_SPI_TX_PIN;
    // static constexpr spi_inst_t *SPI_BUS = spi0;

    FxManager fx;
    Adc adc;
    AudioPwm pwm;
    Button button_back;
    Button button_next;
    Display display;
    Led led;
    Potentiometer gain_pot;
    Switch toggle;
    Switch foot_switch;
};

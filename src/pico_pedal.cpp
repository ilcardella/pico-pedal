#include "pico_pedal.h"

PicoPedal::PicoPedal()
    : fx(Adc::ADC_MIN, Adc::ADC_MAX),
      adc(ADC_SPI_SCK_PIN, ADC_SPI_CS_PIN, ADC_SPI_MISO_PIN, ADC_SPI_MOSI_PIN, spi0),
      pwm(PWM_OUT_1_PIN, PWM_OUT_2_PIN), button_back(BUTTON_BACK_PIN),
      button_next(BUTTON_NEXT_PIN), display(DISPLAY_I2C_SDA, DISPLAY_I2C_SCL, I2C_BUS),
      led(LED_PIN), gain_pot(POTENTIOMETER_PIN, POTENTIOMETER_CH), toggle(TOGGLE_PIN),
      foot_switch(FOOT_SWITCH_PIN)
{
}

void PicoPedal::spin()
{
    std::string message = "";

    // Cycle effects upon button press
    if (button_back.is_pressed_and_released())
    {
        fx.previous_effect();
    }
    else if (button_next.is_pressed_and_released())
    {
        fx.next_effect();
    }

    if (toggle.is_on())
    {
        // Do something when the switch is on
    }
    else
    {
        // Do something when the switch is off
    }

    // Update effect gain based on input potentiometer value
    fx.set_gain(gain_pot.get_percent_value());

    // Perform audio processing only when the footswitch is on
    if (foot_switch.is_on())
    {
        led.on();

        // Read audio input from the ADC
        uint32_t audio_input(adc.read());
        uint32_t audio_output(0);

        // Process audio through the active effect
        if (fx.process(audio_input, audio_output))
        {
            // Send audio output out
            pwm.send(audio_output);
        }
        else
        {
            // If the effect fails, pass through the input audio and show a message
            pwm.send(audio_input);
            message = "Error processing audio";
        }
    }
    else
    {
        led.off();
    }

    // Update display
    display.set_message(message);
    display.set_fx_name(fx.get_effect_name());
    display.show();
}

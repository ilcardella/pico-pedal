#include "pico_pedal.h"

#include <pico/stdlib.h>

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
    uint32_t audio_input(0);
    uint32_t audio_output(0);

    // Process the inputs
    read_inputs();

    // Perform audio processing only when required
    if (enable_audio_fx)
    {
        // Read audio input from the ADC
        audio_input = adc.read();

        // Process audio through the active effect
        if (not fx.process(audio_input, audio_output))
        {
            // If the effect fails, pass through the input audio and show a message
            audio_output = audio_input;
            display.set_message("Error processing audio");
        }
    }

    // Send output through the PWM
    pwm.send(audio_output);

    // TODO could we use the second core for this?
    // Update display
    display.show();
}

void PicoPedal::read_inputs()
{
    auto now = to_ms_since_boot(get_absolute_time());
    if (now - last_input_reading_ts >= INPUT_READ_PERIOD)
    {
        // Cycle effects upon button press
        if (button_back.is_pressed_and_released())
        {
            fx.previous_effect();
        }
        else if (button_next.is_pressed_and_released())
        {
            fx.next_effect();
        }
        display.set_fx_name(fx.get_effect_name());

        // TODO decide what to do with this
        // if (toggle.is_on())
        // {
        //     // Do something when the switch is on
        // }
        // else
        // {
        //     // Do something when the switch is off
        // }
        display.set_toggle_status(toggle.is_on());

        // Update effect gain based on input potentiometer value
        float gain = gain_pot.get_percent_value();
        fx.set_gain(gain);
        display.set_gain_percent(gain);

        // Enable the audio processing when the foot switch is on
        enable_audio_fx = foot_switch.is_on();
        display.set_fx_enabled(enable_audio_fx);
        // Turn also the LED on
        led.set(enable_audio_fx);

        // Store for next iteration
        last_input_reading_ts = now;
    }
}

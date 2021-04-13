#include "pico_pedal.h"

PicoPedal::PicoPedal()
    : fx(), adc(PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN,
                PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN),
      pwm(22, 21), button_back(10), button_next(11), display(2, 3), led(6),
      gain_pot(26, 0), toggle(7), foot_switch(8)
{
}

void PicoPedal::spin()
{
    std::string fx_name = "Off";
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
    fx.set_gain_percentage(gain_pot.get_percent_value());

    // If the footswitch is off skip the audio processing
    if (foot_switch.is_on())
    {
        fx_name = fx.get_effect_name();

        led.on();

        // Read audio input from the ADC
        uint32_t audio_input = adc.read();
        uint32_t audio_output = audio_input;

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
    display.set_fx_name(fx_name);
    display.show();
}

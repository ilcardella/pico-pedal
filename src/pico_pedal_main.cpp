
#include <memory>

#include <guitar_fx_lib/fx_manager.hpp>

#include "hardware/clocks.h"
#include <hardware/i2c.h>
#include <hardware/spi.h>
#include <pico/multicore.h>
#include <pico/stdlib.h>

#include "adc.h"
#include "audio_pwm.h"
#include "button.h"
#include "display.h"
#include "led.h"
#include "potentiometer.h"
#include "switch.h"

constexpr uint PWM_OUT_1_PIN = 22;
constexpr uint PWM_OUT_2_PIN = 21;
constexpr uint BUTTON_BACK_PIN = 10;
constexpr uint BUTTON_NEXT_PIN = 11;
constexpr uint DISPLAY_I2C_SDA = 2;
constexpr uint DISPLAY_I2C_SCL = 3;
constexpr i2c_inst_t *I2C_BUS = i2c1;
constexpr uint LED_PIN = 6;
constexpr uint POTENTIOMETER_PIN = 26;
constexpr uint POTENTIOMETER_CH = 0;
constexpr uint TOGGLE_PIN = 7;
constexpr uint FOOT_SWITCH_PIN = 8;
constexpr uint ADC_SPI_SCK_PIN = PICO_DEFAULT_SPI_SCK_PIN;
constexpr uint ADC_SPI_CS_PIN = PICO_DEFAULT_SPI_CSN_PIN;
constexpr uint ADC_SPI_MISO_PIN = PICO_DEFAULT_SPI_RX_PIN;
constexpr uint ADC_SPI_MOSI_PIN = PICO_DEFAULT_SPI_TX_PIN;
constexpr unsigned long INPUT_READ_PERIOD = 50; // ms
constexpr uint32_t SYSTEM_CLOCK_FREQ_KHZ = 176 * KHZ;

std::unique_ptr<FxManager> fx;
std::unique_ptr<Adc> adc;
std::unique_ptr<AudioPwm> pwm;
std::unique_ptr<Button> button_back;
std::unique_ptr<Button> button_next;
std::unique_ptr<Display> display;
std::unique_ptr<Led> led;
std::unique_ptr<Potentiometer> gain_pot;
std::unique_ptr<Switch> toggle;
std::unique_ptr<Switch> foot_switch;

bool enable_audio_fx = false;
unsigned long last_input_reading_ts = 0UL;

void read_inputs()
{
    auto now = to_ms_since_boot(get_absolute_time());
    if (now - last_input_reading_ts >= INPUT_READ_PERIOD)
    {
        // Cycle effects upon button press
        if (button_back->is_pressed_and_released())
        {
            fx->previous_effect();
        }
        else if (button_next->is_pressed_and_released())
        {
            fx->next_effect();
        }
        display->set_fx_name(fx->get_effect_name());

        // TODO decide what to do with this
        // if (toggle.is_on())
        // {
        //     // Do something when the switch is on
        // }
        // else
        // {
        //     // Do something when the switch is off
        // }
        display->set_toggle_status(toggle->is_on());

        // Update effect gain based on input potentiometer value
        float gain = gain_pot->get_percent_value();
        fx->set_gain(gain);
        display->set_gain_percent(gain);

        // Enable the audio processing when the foot switch is on
        enable_audio_fx = foot_switch->is_on();
        display->set_fx_enabled(enable_audio_fx);
        // Turn also the LED on
        led->set(enable_audio_fx);

        // Store for next iteration
        last_input_reading_ts = now;
    }
}

void core1_routine()
{
    while (true)
    {
        read_inputs();
        display->show();
    }
}

bool setup()
{
    // Setup global platform configuration
    stdio_init_all();

    // Overclock the CPU for a value multiple of common audio sampling rate
    set_sys_clock_khz(SYSTEM_CLOCK_FREQ_KHZ, true);

    // Initialise components
    fx = std::make_unique<FxManager>(Adc::ADC_MIN, Adc::ADC_MAX);
    adc = std::make_unique<Adc>(ADC_SPI_SCK_PIN, ADC_SPI_CS_PIN, ADC_SPI_MISO_PIN,
                                ADC_SPI_MOSI_PIN, spi0);
    pwm = std::make_unique<AudioPwm>(PWM_OUT_1_PIN, PWM_OUT_2_PIN);
    button_back = std::make_unique<Button>(BUTTON_BACK_PIN);
    button_next = std::make_unique<Button>(BUTTON_NEXT_PIN);
    display = std::make_unique<Display>(DISPLAY_I2C_SDA, DISPLAY_I2C_SCL, I2C_BUS);
    led = std::make_unique<Led>(LED_PIN);
    gain_pot = std::make_unique<Potentiometer>(POTENTIOMETER_PIN, POTENTIOMETER_CH);
    toggle = std::make_unique<Switch>(TOGGLE_PIN);
    foot_switch = std::make_unique<Switch>(FOOT_SWITCH_PIN);

    // To not slow down the audio processing, read inputs and update the display on
    // the second core
    multicore_launch_core1(core1_routine);

    // Just to make sure everything is initialised
    sleep_ms(1000);

    return true;
}

void loop()
{
    uint32_t audio_input(0);
    uint32_t audio_output(0);

    // Perform audio processing only when required
    if (enable_audio_fx)
    {
        // Read audio input from the ADC
        audio_input = adc->read();

        // Process audio through the active effect
        if (not fx->process(audio_input, audio_output))
        {
            // If the effect fails, pass through the input audio and show a message
            audio_output = audio_input;
            display->set_message("Error processing audio");
        }
    }

    // Send output through the PWM
    pwm->send(audio_output);
}

int main()
{
    if (not setup())
    {
        return 1;
    }

    while (true)
    {
        loop();
    }
    return 0;
}

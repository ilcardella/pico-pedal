#pragma once

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

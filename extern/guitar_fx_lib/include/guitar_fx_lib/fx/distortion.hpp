#pragma once

#include <guitar_fx_lib/interfaces/effect.hpp>

class Distortion : public Effect
{
  public:
    Distortion() = default;
    ~Distortion() = default;

    // Override this setting values that do not depend on the input signal
    // so that the process() method is as simple as possible
    bool set_gain(const float &value) override
    {
        float threshold_min = 0.02f; // TODO this needs to be verified

        if (value < 0.0f or value > 1.0f)
        {
            return false;
        }

        // Higher values should reduce the threshold window and viceversa
        gain = 1.0f - value;

        float threshold =
            std::max<float>(threshold_min, (signal_max - threshold_min) * gain);
        upper_bound = signal_mid + threshold;
        lower_bound = signal_mid - threshold;
        return true;
    }

    bool apply_fx(const float &input, float &output) override
    {
        // The effect clamp the signal between upper and lower limits
        output = std::min<float>(std::max<float>(input, lower_bound), upper_bound);
        return true;
    }

    std::string get_name() override
    {
        return "Distortion";
    }

  private:
    float upper_bound = 0.0f;
    float lower_bound = 0.0f;
};

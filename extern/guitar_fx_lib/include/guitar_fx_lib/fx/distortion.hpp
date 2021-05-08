#pragma once

#include <guitar_fx_lib/interfaces/effect.hpp>

class Distortion : public Effect
{
  public:
    Distortion(const uint32_t &min, const uint32_t &max)
    {
        set_signal_limits(min, max);
        threshold_min = 0.025f * signal_mid;
    }
    ~Distortion() = default;

    // Override this setting values that do not depend on the input signal
    // so that the process() method is as simple as possible
    void set_gain(const float &value) override
    {
        gain = value;
        uint32_t threshold = std::max<uint32_t>(threshold_min, gain * signal_mid);
        upper_bound = signal_mid + threshold;
        lower_bound = signal_mid - threshold;
    }

    bool process(const uint32_t &input, uint32_t &output) override
    {
        // The effect clamp the signal between upper and lower limits
        output = std::min<uint32_t>(std::max<uint32_t>(input, lower_bound), upper_bound);

        return true;
    }

    std::string get_name()
    {
        return "Distortion";
    }

  private:
    uint32_t threshold_min = 0;
    uint32_t upper_bound = 0;
    uint32_t lower_bound = 0;
};

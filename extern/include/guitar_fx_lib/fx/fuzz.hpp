#pragma once

#include <guitar_fx_lib/interfaces/effect.hpp>

class Fuzz : public Effect
{
  public:
    Fuzz(const uint32_t &min, const uint32_t &max)
    {
        set_signal_limits(min, max);
        threshold_min = 0.025f * signal_mid;
    }
    ~Fuzz() = default;

    void set_gain(const float &value) override
    {
        gain = value;
        uint32_t threshold = std::max<uint32_t>(threshold_min, gain * signal_mid);
        upper_bound = signal_mid + threshold;
        lower_bound = signal_mid - threshold;
    }

    bool process(const uint32_t &input, uint32_t &output) override
    {
        // The effect inflates the signal when outside upper and lower limits
        if (input > upper_bound)
        {
            output = signal_max;
        }
        else if (input < lower_bound)
        {
            output = signal_min;
        }
        else
        {
            output = input;
        }

        return true;
    }

    std::string get_name()
    {
        return "Fuzz";
    }

  private:
    uint32_t threshold_min = 0;
    uint32_t upper_bound = 0;
    uint32_t lower_bound = 0;
};

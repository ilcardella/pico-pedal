#pragma once

#include <memory>
#include <string>

class Effect
{
  public:
    Effect() = default;
    virtual ~Effect() = default;

    virtual bool process(const uint32_t &input, uint32_t &output) = 0;
    virtual std::string get_name() = 0;

    virtual void set_signal_limits(const uint32_t &min, const uint32_t &max)
    {
        signal_max = max;
        signal_min = min;
        signal_mid = (max - min) / 2;
    }

    // Set the effect gain. value must be in range [0.0, 1.0]
    virtual bool set_gain(const float &value)
    {
        if (value < 0.0f or value > 1.0f)
        {
            return false;
        }

        gain = value;

        return true;
    }

  protected:
    // Effect gain in percentage
    float gain = 50;
    // Signal max value
    uint32_t signal_max = 4095;
    // Signal min value
    uint32_t signal_min = 0;
    // Signal middle level
    uint32_t signal_mid = 2047;
};

using EffectPtr = std::unique_ptr<Effect>;

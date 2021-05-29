#pragma once

#include <memory>
#include <string>

class Effect
{
  public:
    Effect() = default;
    virtual ~Effect() = default;

    virtual std::string get_name() = 0;

    virtual bool process(const float &input, float &output)
    {
        if (input < signal_min or input > signal_max)
        {
            return false;
        }

        return apply_fx(input, output);
    }

    // Set the effect gain. value must be in range [0.0, 1.0]
    virtual bool set_gain(const float &value)
    {
        if (value < 0.0f or value > 1.0f)
        {
            return false;
        }

        gain = value;

        on_gain_update(gain);

        return true;
    }

  protected:
    virtual bool apply_fx(const float &input, float &output) = 0;

    virtual void on_gain_update(const float &new_gain)
    {
    }

    // Effect gain in percentage [0-100]
    float gain = 0.0f;
    // Signal max normalised value
    static constexpr float signal_max = 1.0f;
    // Signal min normalised value
    static constexpr float signal_min = -1.0f;
    // Signal middle normalised level
    static constexpr float signal_mid = 0.0f;
};

using EffectPtr = std::unique_ptr<Effect>;

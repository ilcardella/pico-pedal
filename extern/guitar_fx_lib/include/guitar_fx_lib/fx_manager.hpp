#pragma once

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <guitar_fx_lib/fx/effect.hpp>
#include <guitar_fx_lib/fx/effects.hpp>
#include <guitar_fx_lib/fx/fx_factory.hpp>

class FxManager
{
  public:
    FxManager(const uint32_t &min, const uint32_t &max)
        : FxManager(min, max,
                    {Effects::CLEAN, Effects::DISTORTION, Effects::ECHO, Effects::DELAY,
                     Effects::REVERB})
    {
    }

    FxManager(const uint32_t &min, const uint32_t &max,
              const std::vector<Effects> &effects_list)
        : signal_min(min), signal_max(max), factory(), effects(effects_list)
    {
        if (effects.empty())
        {
            // Ideally we would throw, but some platform don't support exceptions
            effects.push_back(Effects::CLEAN);
        }
        effects_it = effects.begin();
        active_fx = factory.make(*effects_it);
    }

    ~FxManager() = default;

    // Set the current effect gain. value must be in range [0.0, 1.0]
    bool set_gain(const float &value)
    {
        if (value < 0.0f or value > 1.0f)
        {
            return false;
        }
        return active_fx->set_gain(value);
    }

    // Select the next effect. Wrap around after the last effect to start from the
    // beginning again
    void next_effect()
    {
        effects_it++;

        if (effects_it == effects.end())
        {
            effects_it = effects.begin();
        }

        active_fx = factory.make(*effects_it);
    }

    // Select the previous effect. Wrap around after the first effect to start from the
    // end again
    void previous_effect()
    {
        if (effects_it == effects.begin())
        {
            effects_it = effects.end() - 1;
        }
        else
        {
            effects_it--;
        }

        active_fx = factory.make(*effects_it);
    }

    // Process an input signal into the current selected effect
    bool process(const uint32_t &input, uint32_t &output)
    {
        float normalised_input(0.0f);
        float normalised_output(0.0f);
        output = 0;

        normalised_input = normalise(input);

        if (active_fx->process(normalised_input, normalised_output))
        {
            output = denormalise(normalised_output);
            return true;
        }

        return false;
    }

    std::string get_active_effect_name()
    {
        return active_fx->get_name();
    }

  private:
    float normalise(const uint32_t &input)
    {
        // Constraint the input before the conversion
        uint32_t safe_input =
            std::min<uint32_t>(std::max<uint32_t>(input, signal_min), signal_max);

        return map(static_cast<float>(safe_input), static_cast<float>(signal_min),
                   static_cast<float>(signal_max), norm_signal_min, norm_signal_max);
    }

    uint32_t denormalise(const float &normalised_output)
    {
        // Constraint the output before the conversion
        float safe_output = std::min<float>(
            std::max<float>(normalised_output, norm_signal_min), norm_signal_max);

        return static_cast<uint32_t>(map(safe_output, norm_signal_min, norm_signal_max,
                                         static_cast<float>(signal_min),
                                         static_cast<float>(signal_max)) +
                                     0.5f); // add .5f to avoid rounding errors
    }

    float map(const float &x, const float &in_min, const float &in_max,
              const float &out_min, const float &out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    const uint32_t signal_max;
    const uint32_t signal_min;
    const float norm_signal_max = 1.0f;
    const float norm_signal_min = -1.0f;

    FxFactory factory;
    std::vector<Effects> effects;
    std::vector<Effects>::iterator effects_it;
    EffectPtr active_fx = nullptr;
};

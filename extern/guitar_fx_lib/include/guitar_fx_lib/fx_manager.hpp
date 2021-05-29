#pragma once

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <guitar_fx_lib/fx/clean.hpp>
#include <guitar_fx_lib/fx/distortion.hpp>
#include <guitar_fx_lib/interfaces/effect.hpp>

class FxManager
{
  public:
    FxManager(const uint32_t &min, const uint32_t &max)
        : signal_min(min), signal_max(max), signal_middle((max - min) / 2)
    {
        effects.push_back(std::make_unique<Clean>());
        effects.push_back(std::make_unique<Distortion>());
        effects_it = effects.begin();
    }

    ~FxManager() = default;

    // Set the current effect gain. value must be in range [0.0, 1.0]
    bool set_gain(const float &value)
    {
        if (value < 0.0f or value > 1.0f)
        {
            return false;
        }
        return (*effects_it)->set_gain(value);
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
    }

    // Process an input signal into the current selected effect
    bool process(const uint32_t &input, uint32_t &output)
    {
        float normalised_input(0.0f);
        float normalised_output(0.0f);
        output = 0;

        normalised_input = normalise_input(input);

        if ((*effects_it)->process(normalised_input, normalised_output))
        {
            output = convert_output(normalised_output);
            return true;
        }

        return false;
    }

    std::string get_active_effect_name()
    {
        return (*effects_it)->get_name();
    }

    std::vector<std::string> get_all_effects_names()
    {
        std::vector<std::string> names;
        std::transform(effects.begin(), effects.end(), std::back_inserter(names),
                       [](const auto &effect) { return effect->get_name(); });
        return names;
    }

  private:
    float normalise_input(const uint32_t &input)
    {
        return (static_cast<float>(input) - signal_middle) / (signal_middle + 1.0f);
    }

    uint32_t convert_output(const float &normalised_output)
    {
        float output(0.0f);

        // Constraint the output before the conversion
        output = std::min<float>(std::max<float>(normalised_output, -1.0f), 1.0f);

        return output * ((signal_middle + 1) + signal_middle);
    }

    uint32_t signal_max;
    uint32_t signal_min;
    uint32_t signal_middle;
    std::vector<EffectPtr> effects;
    std::vector<EffectPtr>::iterator effects_it;
};

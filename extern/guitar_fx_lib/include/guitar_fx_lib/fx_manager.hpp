#pragma once

#include <iterator>
#include <string>
#include <vector>

#include <guitar_fx_lib/fx/clean.hpp>
#include <guitar_fx_lib/fx/distortion.hpp>
#include <guitar_fx_lib/fx/fuzz.hpp>
#include <guitar_fx_lib/interfaces/effect.hpp>

class FxManager
{
  public:
    FxManager(const uint32_t &min, const uint32_t &max)
    {
        effects.push_back(std::make_unique<Clean>(min, max));
        effects.push_back(std::make_unique<Distortion>(min, max));
        effects.push_back(std::make_unique<Fuzz>(min, max));
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
        return (*effects_it)->process(input, output);
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
    std::vector<EffectPtr> effects;
    std::vector<EffectPtr>::iterator effects_it;
};
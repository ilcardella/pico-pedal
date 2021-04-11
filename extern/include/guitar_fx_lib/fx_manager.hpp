#pragma once

#include <memory>
#include <string>

#include <guitar_fx_lib/fx/clean.hpp>
#include <guitar_fx_lib/fx/distortion.hpp>
#include <guitar_fx_lib/interfaces/effect.hpp>

enum class Effects
{
    CLEAN = 0,
    DISTORTION
};

class FxManager
{
  public:
    FxManager()
    {
        // TODO manage multiple effects
        active_effect = std::make_unique<Distortion>();
    }

    ~FxManager() = default;

    void set_gain_percentage(const float &value)
    {
        active_effect->set_gain_percentage(value);
    }

    void next_effect()
    {
        // TODO
    }

    void previous_effect()
    {
        // TODO
    }

    bool process(const uint32_t &input, uint32_t &output)
    {
        return active_effect->process(input, output);
    }

    std::string get_effect_name()
    {
        return active_effect->get_name();
    }

  private:
    std::unique_ptr<Effect> active_effect;
};
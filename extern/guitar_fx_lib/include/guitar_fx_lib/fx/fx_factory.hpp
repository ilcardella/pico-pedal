#pragma once

#include <memory>

#include <guitar_fx_lib/fx/clean.hpp>
#include <guitar_fx_lib/fx/delay.hpp>
#include <guitar_fx_lib/fx/distortion.hpp>
#include <guitar_fx_lib/fx/echo.hpp>
#include <guitar_fx_lib/fx/effect.hpp>
#include <guitar_fx_lib/fx/effects.hpp>
#include <guitar_fx_lib/fx/reverb.hpp>

class FxFactory
{
  public:
    FxFactory() = default;
    ~FxFactory() = default;

    EffectPtr make(const Effects &fx)
    {
        switch (fx)
        {
        case Effects::CLEAN:
            return std::make_unique<Clean>();
        case Effects::DISTORTION:
            return std::make_unique<Distortion>();
        case Effects::ECHO:
            return std::make_unique<Echo>();
        case Effects::DELAY:
            return std::make_unique<Delay>();
        case Effects::REVERB:
            return std::make_unique<Reverb>();
        default:
            return nullptr;
        }
        return nullptr;
    }
};

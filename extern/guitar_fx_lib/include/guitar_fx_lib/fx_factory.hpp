#pragma once

#include <memory>

#include <guitar_fx_lib/fx/clean.hpp>
#include <guitar_fx_lib/fx/delay.hpp>
#include <guitar_fx_lib/fx/distortion.hpp>
#include <guitar_fx_lib/fx/echo.hpp>
#include <guitar_fx_lib/interfaces/effect.hpp>

enum class Effects
{
    CLEAN,
    DISTORTION,
    ECHO,
    DELAY
};

class FxFactory
{
  public:
    FxFactory() = default;
    ~FxFactory() = default;

    std::unique_ptr<Effect> make(const Effects &fx)
    {
        switch (fx)
        {
        case Effects::CLEAN:
            return std::make_unique<Clean>();
            break;
        case Effects::DISTORTION:
            return std::make_unique<Distortion>();
            break;
        case Effects::ECHO:
            return std::make_unique<Echo>();
            break;
        case Effects::DELAY:
            return std::make_unique<Delay>();
            break;

        default:
            return nullptr;
            break;
        }
        return nullptr;
    }
};

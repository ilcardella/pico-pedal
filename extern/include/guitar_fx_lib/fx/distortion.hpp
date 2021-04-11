#pragma once

#include <guitar_fx_lib/interfaces/effect.hpp>

class Distortion : public Effect
{
  public:
    Distortion() = default;
    ~Distortion() = default;

    bool process(const uint32_t &input, uint32_t &output) override
    {
        // TODO
        output = input;

        return true;
    }

    std::string get_name()
    {
        return "Distortion";
    }
};

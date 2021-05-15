#pragma once

#include <guitar_fx_lib/interfaces/effect.hpp>

class Clean : public Effect
{
  public:
    Clean() = default;
    ~Clean() = default;

    bool apply_fx(const float &input, float &output) override
    {
        output = input;
        return true;
    }

    std::string get_name() override
    {
        return "Clean";
    }
};

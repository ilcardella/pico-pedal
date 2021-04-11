#pragma once

#include <guitar_fx_lib/interfaces/effect.hpp>

class Clean : public Effect
{
  public:
    Clean() = default;
    ~Clean() = default;

    bool process(const uint32_t &input, uint32_t &output) override
    {
        output = input;
        return true;
    }

    std::string get_name()
    {
        return "Clean";
    }
};
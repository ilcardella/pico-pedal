#pragma once

#include <guitar_fx_lib/interfaces/effect.hpp>

class Clean : public Effect
{
  public:
    Clean(const uint32_t &min, const uint32_t &max)
    {
        set_signal_limits(min, max);
    }
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
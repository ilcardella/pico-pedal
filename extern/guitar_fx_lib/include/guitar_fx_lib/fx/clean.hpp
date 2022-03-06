#pragma once

#include <guitar_fx_lib/fx/effect.hpp>

class Clean : public Effect
{
  public:
    Clean() = default;
    ~Clean() = default;

    std::string get_name() override
    {
        return "Clean";
    }

  protected:
    bool apply_fx(const float &input, float &output) override
    {
        output = input;
        return true;
    }
};

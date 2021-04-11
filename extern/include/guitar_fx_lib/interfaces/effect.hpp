#pragma once

#include <string>

class Effect
{
  public:
    virtual ~Effect() = default;

    virtual bool process(const uint32_t &input, uint32_t &output) = 0;
    virtual std::string get_name() = 0;

    virtual void set_gain_percentage(const float &value)
    {
        gain = value;
    }

  protected:
    // Effect gain in percentage
    float gain = 50;
};

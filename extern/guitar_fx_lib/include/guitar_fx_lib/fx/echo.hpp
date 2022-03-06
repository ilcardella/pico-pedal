#pragma once

#include <array>

#include <guitar_fx_lib/fx/effect.hpp>

class Echo : public Effect
{
  public:
    Echo() = default;
    ~Echo() = default;

    std::string get_name() override
    {
        return "Echo";
    }

  protected:
    void on_gain_update(const float &new_gain) override
    {
        depth = (DELAY_MAX - DELAY_MIN) * new_gain;
    }

    bool apply_fx(const float &input, float &output) override
    {
        // The effect stores in a buffer the input signals plus the previous buffered
        // output and it repeats the signal with a decay factor

        buffer[counter] = (input + buffer[counter]) / DECAY;
        counter++;
        if (counter >= depth or counter >= DELAY_MAX)
        {
            counter = 0;
        }

        output = (input + buffer[counter]) / DECAY;

        return true;
    }

  private:
    static constexpr uint32_t DELAY_MAX = 20000;
    static constexpr uint32_t DELAY_MIN = 0;
    static constexpr uint32_t DECAY = 4;

    std::array<float, DELAY_MAX> buffer = {0.0f};

    uint32_t counter = 0;
    uint32_t depth = 0;
};

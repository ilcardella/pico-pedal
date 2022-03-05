#pragma once

#include <guitar_fx_lib/fx/delay.hpp>
#include <guitar_fx_lib/interfaces/effect.hpp>

class Reverb : public Effect
{
  public:
    Reverb() : delay1(3000), delay2(2000), delay3(1000)
    {
    }

    ~Reverb() = default;

    std::string get_name() override
    {
        return "Reverb";
    }

  protected:
    void on_gain_update(const float &new_gain) override
    {
        // TODO change the depth of each delay
        // delay1.set_depth(something)
        // delay2.set_depth(something else)
        // delay3.set_depth(another value again)
    }

    bool apply_fx(const float &input, float &output) override
    {
        // The effect simulates 3+ different delays at different depths

        float output1, output2, output3;

        // Remove the input portion from each delay processed signal so that the
        // input can be added only once
        delay1.process(input, output1);
        output1 -= input;
        delay2.process(input, output2);
        output2 -= input;
        delay3.process(input, output3);
        output3 -= input;

        output = (input + output1 + output2 + output3) / DECAY;

        return true;
    }

  private:
    static constexpr uint32_t DECAY = 4;

    Delay delay1;
    Delay delay2;
    Delay delay3;
};

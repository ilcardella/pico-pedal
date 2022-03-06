#pragma once

#include <guitar_fx_lib/fx/effect.hpp>

class Distortion : public Effect
{
  public:
    Distortion() = default;
    ~Distortion() = default;

    std::string get_name() override
    {
        return "Distortion";
    }

  protected:
    bool apply_fx(const float &input, float &output) override
    {
        // The effect clamp the signal between upper and lower limits
        output = std::min<float>(std::max<float>(input, lower_bound), upper_bound);
        return true;
    }

    void on_gain_update(const float &new_gain) override
    {
        // TODO this needs to be verified
        float threshold_min = 0.05f;

        // Higher values should reduce the threshold window and viceversa
        float threshold = std::max<float>(threshold_min, ((signal_max - signal_min) / 2) *
                                                             (1.0f - new_gain));
        upper_bound = signal_mid + threshold;
        lower_bound = signal_mid - threshold;
    }

  private:
    float upper_bound = 0.0f;
    float lower_bound = 0.0f;
};

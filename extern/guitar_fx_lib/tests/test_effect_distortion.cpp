#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/distortion.hpp>

class TestEffectDistortion : public ::testing::Test
{
};

TEST_F(TestEffectDistortion, testEffectInit)
{
    ASSERT_NO_THROW(Distortion dist(0, 1));

    Distortion dist(0, 1);
    ASSERT_EQ(dist.get_name(), "Distortion");
}

TEST_F(TestEffectDistortion, testSetGain)
{
    Distortion dist(0, 1);

    ASSERT_TRUE(dist.set_gain(0.0f));
    ASSERT_TRUE(dist.set_gain(0.12f));
    ASSERT_TRUE(dist.set_gain(0.7f));
    ASSERT_TRUE(dist.set_gain(1.0f));

    ASSERT_FALSE(dist.set_gain(-1.0f));
    ASSERT_FALSE(dist.set_gain(-0.1f));
    ASSERT_FALSE(dist.set_gain(1.1f));
    ASSERT_FALSE(dist.set_gain(100.1f));
}

TEST_F(TestEffectDistortion, testProcessValidSignal)
{
    uint32_t min = 0;
    uint32_t max = 4095;
    uint32_t mid = (max - min) / 2;
    uint32_t output = 0;
    uint32_t threshold_min = 3;   // From effect implementation
    uint32_t threshold_max = mid; // From effect implementation
    float gain = 0.2f;            // = 80%

    uint32_t threshold =
        std::max<uint32_t>(threshold_min, (threshold_max - threshold_min) * (1 - gain));
    uint32_t upper_threshold = mid + threshold;
    uint32_t lower_threshold = mid - threshold;

    Distortion dist(min, max);
    dist.set_gain(gain);

    for (uint32_t input = 0; input < max + 1; ++input)
    {
        ASSERT_TRUE(dist.process(input, output));

        if (input > upper_threshold)
        {
            ASSERT_EQ(output, upper_threshold);
        }
        else if (input < lower_threshold)
        {
            ASSERT_EQ(output, lower_threshold);
        }
        else
        {
            ASSERT_EQ(output, input);
        }
    }
}

TEST_F(TestEffectDistortion, testProcessInvalidSignal)
{
    uint32_t output = 0;

    Distortion dist(0, 4095);

    for (uint32_t input = 4096; input < 8000; ++input)
    {
        ASSERT_FALSE(dist.process(input, output));
        ASSERT_EQ(0, output);
    }
}

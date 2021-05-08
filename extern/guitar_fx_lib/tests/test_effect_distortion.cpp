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
    float gain = 0.8f;

    uint32_t upper_threshold = mid + (mid * gain);
    uint32_t lower_threshold = mid - (mid * gain) + 1;

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

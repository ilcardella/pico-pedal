#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/distortion.hpp>

class TestEffectDistortion : public ::testing::Test
{
};

TEST_F(TestEffectDistortion, testEffectInit)
{
    ASSERT_NO_THROW(Distortion dist);

    Distortion dist;
    ASSERT_EQ(dist.get_name(), "Distortion");
}

TEST_F(TestEffectDistortion, testSetGain)
{
    Distortion dist;

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
    float output = 0.0f;
    const float threshold_min = 0.05f; // From effect implementation

    for (float gain = 0.0f; gain <= 1.0f; gain += 0.1f)
    {
        // Expected thresholds, these depends on the fx implementation
        const float threshold = std::max<float>(threshold_min, (1 - gain));
        const float upper_threshold = threshold;
        const float lower_threshold = -threshold;

        Distortion dist;
        dist.set_gain(gain);

        for (float input = -1.0f; input <= 1.0f; input += 0.1f)
        {
            ASSERT_TRUE(dist.process(input, output))
                << "Failed with input " << input << " and gain " << gain;

            if (input > upper_threshold)
            {
                ASSERT_EQ(output, upper_threshold)
                    << "Failed with input " << input << " and gain " << gain;
            }
            else if (input < lower_threshold)
            {
                ASSERT_EQ(output, lower_threshold)
                    << "Failed with input " << input << " and gain " << gain;
            }
            else
            {
                ASSERT_EQ(output, input)
                    << "Failed with input " << input << " and gain " << gain;
            }
        }
    }
}

TEST_F(TestEffectDistortion, testProcessInvalidSignal)
{
    float output = 0;

    Distortion dist;

    for (float input = -100.0f; input <= 100.0f; input += 0.1f)
    {
        if (input < -1.0f or input > 1.0f)
        {
            ASSERT_FALSE(dist.process(input, output));
            ASSERT_EQ(0, output);
        }
    }
}

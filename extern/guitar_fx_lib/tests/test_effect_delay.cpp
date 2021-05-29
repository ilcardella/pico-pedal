#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/delay.hpp>

class TestEffectDelay : public ::testing::Test
{
};

TEST_F(TestEffectDelay, testEffectInit)
{
    ASSERT_NO_THROW(Delay delay);

    Delay delay;
    ASSERT_EQ(delay.get_name(), "Delay");
}

TEST_F(TestEffectDelay, testSetGain)
{
    Delay delay;

    ASSERT_TRUE(delay.set_gain(0.0f));
    ASSERT_TRUE(delay.set_gain(0.12f));
    ASSERT_TRUE(delay.set_gain(0.7f));
    ASSERT_TRUE(delay.set_gain(1.0f));

    ASSERT_FALSE(delay.set_gain(-1.0f));
    ASSERT_FALSE(delay.set_gain(-0.1f));
    ASSERT_FALSE(delay.set_gain(1.1f));
    ASSERT_FALSE(delay.set_gain(100.1f));
}

TEST_F(TestEffectDelay, testProcessValidSignal)
{
    float output = 0.0f;
    float gain = 0.8f;
    float previous_input = 0.0f;
    uint32_t decay_factor = 2; // from effect implementation

    Delay delay;
    delay.set_gain(gain);

    for (float input = -1.0f; input <= 1.0f; input += 0.1f)
    {
        ASSERT_TRUE(delay.process(input, output));

        // This loop won't fill in the internal effect buffer, hence the + 0
        float expected_output = (input + 0.0f) / decay_factor;
        ASSERT_EQ(expected_output, output);
    }
}

TEST_F(TestEffectDelay, testProcessInvalidSignal)
{
    float output = 0;

    Delay delay;

    for (float input = -100.0f; input <= 100.0f; input += 0.1f)
    {
        if (input < -1.0f or input > 1.0f)
        {
            ASSERT_FALSE(delay.process(input, output));
            ASSERT_EQ(0, output);
        }
    }
}

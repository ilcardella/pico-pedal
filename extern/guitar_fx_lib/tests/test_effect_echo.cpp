#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/echo.hpp>

class TestEffectEcho : public ::testing::Test
{
};

TEST_F(TestEffectEcho, testEffectInit)
{
    ASSERT_NO_THROW(Echo echo);

    Echo echo;
    ASSERT_EQ(echo.get_name(), "Echo");
}

TEST_F(TestEffectEcho, testSetGain)
{
    Echo echo;

    ASSERT_TRUE(echo.set_gain(0.0f));
    ASSERT_TRUE(echo.set_gain(0.12f));
    ASSERT_TRUE(echo.set_gain(0.7f));
    ASSERT_TRUE(echo.set_gain(1.0f));

    ASSERT_FALSE(echo.set_gain(-1.0f));
    ASSERT_FALSE(echo.set_gain(-0.1f));
    ASSERT_FALSE(echo.set_gain(1.1f));
    ASSERT_FALSE(echo.set_gain(100.1f));
}

TEST_F(TestEffectEcho, testProcessValidSignal)
{
    float output = 0.0f;
    float gain = 0.8f;
    float previous_input = 0.0f;
    uint32_t decay_factor = 4; // from effect implementation

    Echo echo;
    echo.set_gain(gain);

    for (float input = -1.0f; input <= 1.0f; input += 0.1f)
    {
        ASSERT_TRUE(echo.process(input, output));

        // This loop won't fill in the internal effect buffer, hence the + 0
        float expected_output = (input + 0.0f) / decay_factor;
        ASSERT_EQ(expected_output, output);
    }
}

TEST_F(TestEffectEcho, testProcessInvalidSignal)
{
    float output = 0;

    Echo echo;

    for (float input = -100.0f; input <= 100.0f; input += 0.1f)
    {
        if (input < -1.0f or input > 1.0f)
        {
            ASSERT_FALSE(echo.process(input, output));
            ASSERT_EQ(0, output);
        }
    }
}

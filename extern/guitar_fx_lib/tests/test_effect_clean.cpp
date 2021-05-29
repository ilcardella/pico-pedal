#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/clean.hpp>

class TestEffectClean : public ::testing::Test
{
};

TEST_F(TestEffectClean, testEffectInit)
{
    ASSERT_NO_THROW(Clean clean());

    Clean clean;
    ASSERT_EQ(clean.get_name(), "Clean");
}

TEST_F(TestEffectClean, testSetGain)
{
    Clean clean;

    ASSERT_TRUE(clean.set_gain(0.0f));
    ASSERT_TRUE(clean.set_gain(0.12f));
    ASSERT_TRUE(clean.set_gain(0.7f));
    ASSERT_TRUE(clean.set_gain(1.0f));

    ASSERT_FALSE(clean.set_gain(-1.0f));
    ASSERT_FALSE(clean.set_gain(-0.1f));
    ASSERT_FALSE(clean.set_gain(1.1f));
    ASSERT_FALSE(clean.set_gain(100.1f));
}

TEST_F(TestEffectClean, testProcessValidSignal)
{
    float output = 0.0f;

    Clean clean;

    for (float input = -1.0f; input <= 1.0f; input += 0.1f)
    {
        ASSERT_TRUE(clean.process(input, output));
        ASSERT_EQ(input, output);
    }
}

TEST_F(TestEffectClean, testProcessInvalidSignal)
{
    float output = 0.0f;

    Clean clean;

    for (float input = -100.0f; input <= 100.0f; input += 0.1f)
    {
        if (input < -1.0f or input > 1.0f)
        {
            ASSERT_FALSE(clean.process(input, output));
            ASSERT_EQ(0, output);
        }
    }
}

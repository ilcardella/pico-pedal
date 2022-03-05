#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/reverb.hpp>

class TestEffectReverb : public ::testing::Test
{
};

TEST_F(TestEffectReverb, testEffectInit)
{
    ASSERT_NO_THROW(Reverb());

    Reverb rev;
    ASSERT_EQ(rev.get_name(), "Reverb");
}

TEST_F(TestEffectReverb, testSetGain)
{
    Reverb rev;

    ASSERT_TRUE(rev.set_gain(0.0f));
    ASSERT_TRUE(rev.set_gain(0.12f));
    ASSERT_TRUE(rev.set_gain(0.7f));
    ASSERT_TRUE(rev.set_gain(1.0f));

    ASSERT_FALSE(rev.set_gain(-1.0f));
    ASSERT_FALSE(rev.set_gain(-0.1f));
    ASSERT_FALSE(rev.set_gain(1.1f));
    ASSERT_FALSE(rev.set_gain(100.1f));
}

TEST_F(TestEffectReverb, testProcessValidSignal)
{
    float output = 0.0f;

    Reverb rev;
    rev.set_gain(0.5f);

    for (float input = -1.0f; input <= 1.0f; input += 0.1f)
    {
        ASSERT_TRUE(rev.process(input, output)) << "Failed with input " << input;
        ASSERT_GE(output, -1.0f);
        ASSERT_LE(output, 1.0f);
    }
}

TEST_F(TestEffectReverb, testProcessInvalidSignal)
{
    float output = 0;

    Reverb rev;

    for (float input = -100.0f; input <= 100.0f; input += 0.1f)
    {
        if (input < -1.0f or input > 1.0f)
        {
            ASSERT_FALSE(rev.process(input, output));
            ASSERT_EQ(0, output);
        }
    }
}

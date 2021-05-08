#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/clean.hpp>

class TestEffectClean : public ::testing::Test
{
};

TEST_F(TestEffectClean, testEffectInit)
{
    ASSERT_NO_THROW(Clean clean(0, 1));

    Clean clean(0, 1);
    ASSERT_EQ(clean.get_name(), "Clean");
}

TEST_F(TestEffectClean, testSetGain)
{
    Clean clean(0, 1);

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
    uint32_t output = 0;

    Clean clean(0, 4095);

    for (uint32_t input = 0; input < 4096; ++input)
    {
        ASSERT_TRUE(clean.process(input, output));
        ASSERT_EQ(input, output);
    }
}

TEST_F(TestEffectClean, testProcessInvalidSignal)
{
    uint32_t output = 0;

    Clean clean(0, 4095);

    for (uint32_t input = 4096; input < 8000; ++input)
    {
        ASSERT_FALSE(clean.process(input, output));
        ASSERT_EQ(0, output);
    }
}

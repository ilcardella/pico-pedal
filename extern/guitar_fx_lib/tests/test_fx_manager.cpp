#include <gtest/gtest.h>

#include <guitar_fx_lib/fx_manager.hpp>

class TestFxManager : public ::testing::Test
{
};

TEST_F(TestFxManager, testInitialisation)
{
    // Ideally these should throw, but exceptions are disabled
    ASSERT_NO_THROW(FxManager fx0(0, 0));
    ASSERT_NO_THROW(FxManager fx1(1, 0));
    ASSERT_NO_THROW(FxManager fx2(-1, 0));
    ASSERT_NO_THROW(FxManager fx3(0, -1));
    ASSERT_NO_THROW(FxManager fx4(-10, -1));

    FxManager fx(0, 1);
    auto names = fx.get_all_effects_names();
    ASSERT_EQ(names.size(), 3);
    ASSERT_EQ(names[0], "Clean");
    ASSERT_EQ(names[1], "Distortion");
    ASSERT_EQ(names[2], "Fuzz");
}

TEST_F(TestFxManager, testCycleThroughNextEffects)
{
    FxManager fx(0, 4095);
    unsigned int index = 0;
    auto names = fx.get_all_effects_names();

    ASSERT_EQ(fx.get_active_effect_name(), names[index % names.size()]);

    // Verify that it cycles through the effects in both directions
    for (unsigned i = 0; i < 100; ++i)
    {
        ASSERT_NO_THROW(fx.next_effect());
        index++;
        ASSERT_EQ(fx.get_active_effect_name(), names[index % names.size()]);
    }
}

TEST_F(TestFxManager, testCycleThroughPreviousEffects)
{
    FxManager fx(0, 4095);
    unsigned int index = 0;
    auto names = fx.get_all_effects_names();

    ASSERT_EQ(fx.get_active_effect_name(), names[index % names.size()]);

    // Verify that it cycles through the effects in both directions
    for (unsigned i = 0; i < 100; ++i)
    {
        ASSERT_NO_THROW(fx.previous_effect());
        ASSERT_EQ(fx.get_active_effect_name(),
                  names[names.size() - 1 - (index % names.size())]);
        index++;
    }
}

TEST_F(TestFxManager, testSetGain)
{
    FxManager fx(0, 4095);
    ASSERT_TRUE(fx.set_gain(0.0f));
    ASSERT_TRUE(fx.set_gain(0.1f));
    ASSERT_TRUE(fx.set_gain(0.45f));
    ASSERT_TRUE(fx.set_gain(0.1f));

    ASSERT_FALSE(fx.set_gain(-1.0f));
    ASSERT_FALSE(fx.set_gain(-0.2f));
    ASSERT_FALSE(fx.set_gain(1.1f));
    ASSERT_FALSE(fx.set_gain(100));
}

TEST_F(TestFxManager, testProcessSignal)
{
    FxManager fx(0, 4095);
    uint32_t input = 100;
    uint32_t output = 0;

    auto names = fx.get_all_effects_names();
    for (unsigned i = 0; i < names.size(); ++i)
    {
        ASSERT_TRUE(fx.process(input, output));
        ASSERT_NO_THROW(fx.next_effect());
    }
}

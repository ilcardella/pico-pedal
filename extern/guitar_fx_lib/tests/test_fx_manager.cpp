#include <gtest/gtest.h>

#include <guitar_fx_lib/fx_manager.hpp>

class TestFxManager : public ::testing::Test
{
};

TEST_F(TestFxManager, test1)
{
    FxManager fx(0, 1);
    ASSERT_EQ(1 + 1, 2);
}

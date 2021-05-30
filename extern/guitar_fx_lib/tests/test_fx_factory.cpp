#include <memory>
#include <tuple>

#include <gtest/gtest.h>

#include <guitar_fx_lib/fx/clean.hpp>
#include <guitar_fx_lib/fx/delay.hpp>
#include <guitar_fx_lib/fx/distortion.hpp>
#include <guitar_fx_lib/fx/echo.hpp>
#include <guitar_fx_lib/fx_factory.hpp>

class TestFxFactory
    : public ::testing::TestWithParam<std::tuple<Effects, std::shared_ptr<Effect>>>
{
};

TEST_P(TestFxFactory, testMakeValidFx)
{
    FxFactory factory;

    auto type = std::get<0>(GetParam());
    auto mock = std::get<1>(GetParam());

    auto fx = factory.make(type);
    ASSERT_NE(fx, nullptr);
    EXPECT_EQ(typeid(*mock), typeid(*fx));
}

INSTANTIATE_TEST_CASE_P(
    FxFactoryTests, TestFxFactory,
    ::testing::Values(std::make_tuple(Effects::CLEAN, std::make_shared<Clean>()),
                      std::make_tuple(Effects::DISTORTION,
                                      std::make_shared<Distortion>()),
                      std::make_tuple(Effects::ECHO, std::make_shared<Echo>()),
                      std::make_tuple(Effects::DELAY, std::make_shared<Delay>())));
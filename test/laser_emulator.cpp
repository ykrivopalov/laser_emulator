/**
@brief   Laser emulator test.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#include <lib/laser_emulator.h>

#include <gtest/gtest.h>

#include <memory>
#include <thread>

const unsigned int INITIAL_POWER = 1;
const unsigned int KEEP_ALIVE_TIMEOUT = 1; // s

using namespace std::chrono_literals;

class LaserEmulator : public testing::Test {
public:
  void SetUp() override {
    laser = std::make_unique<laser_emulator::LaserEmulator>(INITIAL_POWER,
                                                            KEEP_ALIVE_TIMEOUT);
  }

  void TearDown() override { laser.reset(); }

protected:
  std::unique_ptr<laser_emulator::LaserEmulator> laser;
};

TEST_F(LaserEmulator, StartsAndStops) {
  EXPECT_FALSE(laser->Status());

  EXPECT_NO_THROW(laser->Start());
  EXPECT_THROW(laser->Start(), laser_emulator::LaserError);

  EXPECT_TRUE(laser->Status());

  EXPECT_NO_THROW(laser->Stop());
  EXPECT_THROW(laser->Stop(), laser_emulator::LaserError);

  EXPECT_FALSE(laser->Status());
}

TEST_F(LaserEmulator, AllowsToSetPowerOnlyWhenStarted) {
  EXPECT_THROW(laser->SetPower(1), laser_emulator::LaserError);
  laser->Start();

  EXPECT_NO_THROW(laser->SetPower(1));
  EXPECT_EQ(1, laser->Power());

  laser->Stop();

  EXPECT_THROW(laser->SetPower(1), laser_emulator::LaserError);
}

TEST_F(LaserEmulator, HasZeroPowerWhenStopped) {
  EXPECT_EQ(0, laser->Power());
  laser->Start();
  laser->SetPower(1);
  laser->Stop();
  EXPECT_EQ(0, laser->Power());
}

TEST_F(LaserEmulator, AllowsToSetPowerOnlyWithinAllowedBoundaries) {
  laser->Start();

  EXPECT_NO_THROW(laser->SetPower(1));
  EXPECT_EQ(1, laser->Power());

  EXPECT_THROW(laser->SetPower(101), laser_emulator::LaserError);
  EXPECT_THROW(laser->SetPower(0), laser_emulator::LaserError);
  EXPECT_EQ(1, laser->Power());

  EXPECT_NO_THROW(laser->SetPower(100));
  EXPECT_EQ(100, laser->Power());
}

TEST_F(LaserEmulator, StopsWithoutKeepAlive) {
  laser->Start();
  std::this_thread::sleep_for(750ms);
  EXPECT_TRUE(laser->Status());
  std::this_thread::sleep_for(1500ms);
  EXPECT_FALSE(laser->Status());
}

TEST_F(LaserEmulator, WorksWithKeepAlives) {
  laser->Start();
  std::this_thread::sleep_for(750ms);
  laser->KeepAlive();
  std::this_thread::sleep_for(1500ms);
  EXPECT_TRUE(laser->Status());
}

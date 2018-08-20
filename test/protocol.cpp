/**
@brief   Protocol conformance test.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#include "mock/laser.h"

#include <lib/protocol.h>

#include <gtest/gtest.h>

using namespace testing;

TEST(TranslateCall, ReturnsSuccessfullAnswer) {
  StrictMock<laser_emulator::MockLaser> laser;

  EXPECT_CALL(laser, Start());
  EXPECT_EQ("STR#", laser_emulator::TranslateCall(laser, "STR"));

  EXPECT_CALL(laser, Stop());
  EXPECT_EQ("STP#", laser_emulator::TranslateCall(laser, "STP"));

  EXPECT_CALL(laser, Status()).WillOnce(Return(true));
  EXPECT_EQ("ST?|1#", laser_emulator::TranslateCall(laser, "ST?"));

  EXPECT_CALL(laser, KeepAlive());
  EXPECT_EQ("KAL#", laser_emulator::TranslateCall(laser, "KAL"));

  EXPECT_CALL(laser, Power()).WillOnce(Return(10));
  EXPECT_EQ("PW?|10#", laser_emulator::TranslateCall(laser, "PW?"));

  EXPECT_CALL(laser, SetPower(_));
  EXPECT_EQ("PW=#", laser_emulator::TranslateCall(laser, "PW=|10"));
}

TEST(TranslateCall, ReturnsErrorOnException) {
  StrictMock<laser_emulator::MockLaser> laser;

  laser_emulator::LaserError laser_error("SomeError");

  EXPECT_CALL(laser, Start()).WillOnce(Throw(laser_error));
  EXPECT_EQ("STR!", laser_emulator::TranslateCall(laser, "STR"));

  EXPECT_CALL(laser, SetPower(_)).WillOnce(Throw(laser_error));
  EXPECT_EQ("PW=!", laser_emulator::TranslateCall(laser, "PW=|10"));
}

TEST(TranslateCall, ReturnsErrorOnMalformedRequest) {
  StrictMock<laser_emulator::MockLaser> laser;

  laser_emulator::LaserError laser_error("SomeError");

  EXPECT_CALL(laser, SetPower(_)).WillOnce(Throw(laser_error));
  EXPECT_EQ("PW=!", laser_emulator::TranslateCall(laser, "PW=|10"));

  EXPECT_EQ("PW=!", laser_emulator::TranslateCall(laser, "PW=|abc"));
  EXPECT_EQ("PW=!", laser_emulator::TranslateCall(laser, "PW="));
}

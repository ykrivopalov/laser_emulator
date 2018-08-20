/**
@brief   Protocol conformance test.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#include "mock/laser.h"

#include <lib/protocol.h>

#include <gtest/gtest.h>

using namespace testing;

class CommandTranslator : public Test {
public:
  void SetUp() override {
    laser = std::make_unique<StrictMockLaser>();
    translator = std::make_unique<laser_emulator::CommandTranslator>(*laser);
  }

  void TearDown() override {
    translator.reset();
    laser.reset();
  }

protected:
  typedef StrictMock<laser_emulator::MockLaser> StrictMockLaser;
  std::unique_ptr<StrictMockLaser> laser;
  std::unique_ptr<laser_emulator::CommandTranslator> translator;
};

TEST_F(CommandTranslator, ReturnsSuccessfullAnswer) {
  EXPECT_CALL(*laser, Start());
  EXPECT_EQ("STR#", translator->Translate("STR"));

  EXPECT_CALL(*laser, Stop());
  EXPECT_EQ("STP#", translator->Translate("STP"));

  EXPECT_CALL(*laser, Status()).WillOnce(Return(true));
  EXPECT_EQ("ST?|1#", translator->Translate("ST?"));

  EXPECT_CALL(*laser, KeepAlive());
  EXPECT_EQ("KAL#", translator->Translate("KAL"));

  EXPECT_CALL(*laser, Power()).WillOnce(Return(10));
  EXPECT_EQ("PW?|10#", translator->Translate("PW?"));

  EXPECT_CALL(*laser, SetPower(_));
  EXPECT_EQ("PW=#", translator->Translate("PW=|10"));
}

TEST_F(CommandTranslator, ReturnsErrorOnException) {
  laser_emulator::LaserError laser_error("SomeError");

  EXPECT_CALL(*laser, Start()).WillOnce(Throw(laser_error));
  EXPECT_EQ("STR!", translator->Translate("STR"));

  EXPECT_CALL(*laser, SetPower(_)).WillOnce(Throw(laser_error));
  EXPECT_EQ("PW=!", translator->Translate("PW=|10"));
}

TEST_F(CommandTranslator, ReturnsErrorOnMalformedRequest) {
  laser_emulator::LaserError laser_error("SomeError");

  EXPECT_CALL(*laser, SetPower(_)).WillOnce(Throw(laser_error));
  EXPECT_EQ("PW=!", translator->Translate("PW=|10"));

  EXPECT_EQ("PW=!", translator->Translate("PW=|abc"));
  EXPECT_EQ("PW=!", translator->Translate("PW="));
}

TEST_F(CommandTranslator, SupportsSillyMode) {
  EXPECT_EQ("ESM#", translator->Translate("ESM"));

  EXPECT_CALL(*laser, Start());
  EXPECT_EQ("STR#", translator->Translate("RTS"));

  EXPECT_CALL(*laser, Status()).WillOnce(Return(true));
  EXPECT_EQ("ST?|1#", translator->Translate("?TS"));

  EXPECT_CALL(*laser, Power()).WillOnce(Return(10));
  EXPECT_EQ("PW?|10#", translator->Translate("?WP"));

  EXPECT_CALL(*laser, SetPower(_));
  EXPECT_EQ("PW=#", translator->Translate("01|=WP"));

  EXPECT_EQ("DSM#", translator->Translate("DSM"));

  EXPECT_CALL(*laser, Stop());
  EXPECT_EQ("STP#", translator->Translate("STP"));
}

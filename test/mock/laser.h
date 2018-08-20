#include <gmock/gmock.h>

#include <lib/laser.h>

namespace laser_emulator {

class MockLaser : public Laser {
public:
  MOCK_METHOD0(Start, void());
  MOCK_METHOD0(Stop, void());
  MOCK_CONST_METHOD0(Status, bool());
  MOCK_METHOD0(KeepAlive, void());
  MOCK_CONST_METHOD0(Power, std::uint8_t());
  MOCK_METHOD1(SetPower, void(std::uint8_t value));
};

} // namespace laser_emulator

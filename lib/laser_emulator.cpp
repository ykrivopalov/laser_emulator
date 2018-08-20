/**
@brief   Laser emulator.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#include "laser_emulator.h"

namespace laser_emulator {

LaserEmulator::LaserEmulator(std::uint8_t power,
                             unsigned int keep_alive_timeout)
    : keep_alive_timeout_(keep_alive_timeout), status_(false), power_(power),
      last_time_alive_(0) {}

void LaserEmulator::Start() {
  if (Status())
    throw LaserError("Fail to start laser, it's already on");

  status_ = true;
  last_time_alive_ = std::time(0);
}

void LaserEmulator::Stop() {
  if (!Status())
    throw LaserError("Fail to top laser, it's already off");

  status_ = false;
}

bool LaserEmulator::Status() const {
  UpdateStatus();
  return status_;
}

void LaserEmulator::KeepAlive() {
  if (!Status())
    throw LaserError("Can't keep alive stopped laser");

  last_time_alive_ = std::time(0);
}

std::uint8_t LaserEmulator::Power() const { return Status() ? power_ : 0; }

void LaserEmulator::SetPower(std::uint8_t value) {
  if (!Status())
    throw LaserError("Fail to set power, laser is off");

  if (!value || value > 100)
    throw LaserError("Fail to set power, value should be in the range 1-100");

  power_ = value;
}

void LaserEmulator::UpdateStatus() const {
  if (!status_)
    return;

  const auto now = std::time(0);
  if (now - last_time_alive_ > keep_alive_timeout_)
    status_ = false;
}

} // namespace laser_emulator

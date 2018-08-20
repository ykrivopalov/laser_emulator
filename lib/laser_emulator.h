/**
@brief   Laser emulator.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#pragma once

#include "laser.h"

#include <ctime>

namespace laser_emulator {

/// @brief Laser emulator
/// @note thread unsafe
class LaserEmulator : public Laser {
public:
  /// @param power is initial power level after laser start
  /// @keep_alive_timeout is maximal timeout between KeepAlive requests before
  /// laser stops
  LaserEmulator(std::uint8_t power, unsigned int keep_alive_timeout);

  void Start() override;
  void Stop() override;
  bool Status() const override;
  void KeepAlive() override;
  std::uint8_t Power() const override;
  void SetPower(std::uint8_t value) override;

private:
  void UpdateStatus() const;

  const unsigned int keep_alive_timeout_;

  // mutable, because implementation lazily checks keep alive timeout,
  // so status_ changes only under supervision
  mutable bool status_;
  std::uint8_t power_;
  std::time_t last_time_alive_;
};

} // namespace laser_emulator

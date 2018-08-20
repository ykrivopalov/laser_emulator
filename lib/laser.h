/**
@brief   Laser interface.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#pragma once

#include <cstdint>
#include <exception>
#include <string>

namespace laser_emulator {

class LaserError : public std::exception {
public:
  LaserError(const std::string &msg) : msg_(msg) {}

  const char *what() const noexcept { return msg_.c_str(); }

private:
  const std::string msg_;
};

class Laser {
public:
  virtual ~Laser() {}

  /// @brief Start laser
  /// @detail command 'STR'
  virtual void Start() = 0;

  /// @brief Stop laser
  /// @detail command 'STP'
  virtual void Stop() = 0;

  /// @brief Checks laser's state
  /// @return true if laser is started
  /// @detail command 'ST?'
  virtual bool Status() const = 0;

  /// @brief Keep laser on
  /// @detail command 'KAL'
  virtual void KeepAlive() = 0;

  /// @brief Checks current power level
  /// @return current power value or 0 if laser stopped
  /// @detail command 'PW?'
  virtual std::uint8_t Power() const = 0;

  /// @brief Sets current laser power
  /// @param value in range 1-100
  /// @detail command 'PW='
  virtual void SetPower(std::uint8_t value) = 0;
};

} // namespace laser_emulator

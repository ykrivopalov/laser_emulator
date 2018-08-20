/**
@brief   Laser protocol implementation.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#pragma once

#include <string>

namespace laser_emulator {

class Laser;

/// @brief Translates laser protocol command to Laser interface call
class CommandTranslator {
public:
  CommandTranslator(Laser &laser);

  /// @return laser protocol response
  std::string Translate(const std::string &command);

private:
  Laser& laser_;
  bool silly_mode_;
};

} // namespace laser_emulator

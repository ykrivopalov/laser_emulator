/**
@brief   Laser protocol implementation.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#pragma once

#include <string>

namespace laser_emulator {

class Laser;

/// @brief Translates laser protocol command to Laser interface call
/// @return laser protocol response
std::string TranslateCall(Laser &laser, const std::string &command);

} // namespace laser_emulator

/**
@brief   Laser protocol implementation.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#include "protocol.h"
#include "laser.h"

#include <sstream>

namespace laser_emulator {
namespace {

template <typename T>
std::string MakeReturnValue(const std::string &command, T value) {
  std::ostringstream buf;
  buf << command << "|" << value << "#";
  return buf.str();
}

} // namespace

std::string TranslateCall(Laser &laser, const std::string &command) {
  try {
    if (command == "STR")
      laser.Start();
    else if (command == "STP")
      laser.Stop();
    else if (command == "ST?")
      return MakeReturnValue(command, laser.Status());
    else if (command == "KAL")
      laser.KeepAlive();
    else if (command == "PW?")
      return MakeReturnValue(command, static_cast<int>(laser.Power()));
    else if (!command.compare(0, 3, "PW=")) {
      try {
        if (command.size() < 4 || command[3] != '|')
          return "PW=!";

        const int value = std::stoi(command.substr(4));
        if (value < 1 || value > 100)
          return "PW=!";

        laser.SetPower(value);
        return "PW=#";
      } catch (...) {
        return "PW=!";
      }
    } else
      return "UK!";

    return command + "#";
  } catch (const LaserError & /*error*/) {
    return command + "!";
  }
}

} // namespace laser_emulator

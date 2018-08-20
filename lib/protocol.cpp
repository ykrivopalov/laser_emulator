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

CommandTranslator::CommandTranslator(Laser &laser)
    : laser_(laser), silly_mode_(false) {}

std::string CommandTranslator::Translate(const std::string &raw_command) {
  const std::string command =
      silly_mode_ ? std::string(raw_command.rbegin(), raw_command.rend())
                  : raw_command;

  try {
    if (command == "STR")
      laser_.Start();
    else if (command == "STP")
      laser_.Stop();
    else if (command == "ST?")
      return MakeReturnValue(command, laser_.Status());
    else if (command == "KAL")
      laser_.KeepAlive();
    else if (command == "PW?")
      return MakeReturnValue(command, static_cast<int>(laser_.Power()));
    else if (!command.compare(0, 3, "PW=")) {
      try {
        if (command.size() < 4 || command[3] != '|')
          return "PW=!";

        const int value = std::stoi(command.substr(4));
        if (value < 1 || value > 100)
          return "PW=!";

        laser_.SetPower(value);
        return "PW=#";
      } catch (...) {
        return "PW=!";
      }
    } else if (!silly_mode_ && command == "ESM")
      silly_mode_ = true;
    else if (silly_mode_ && command == "MSD") { // reversed DSM
      silly_mode_ = false;
      return "DSM#";
    } else
      return "UK!";

    return command + "#";
  } catch (const LaserError & /*error*/) {
    return command + "!";
  }
}

} // namespace laser_emulator

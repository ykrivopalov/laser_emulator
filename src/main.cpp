/**
@brief   Laser emulator tool.
@author  Yury Krivopalov (ykrivopalov@yandex.ru)
*/

#include <lib/laser_emulator.h>
#include <lib/protocol.h>

#include <iostream>

const unsigned int INITIAL_POWER = 1;
const unsigned int KEEP_ALIVE_TIMEOUT = 5; // s

int main() {
  laser_emulator::LaserEmulator laser(INITIAL_POWER, KEEP_ALIVE_TIMEOUT);
  laser_emulator::CommandTranslator translator(laser);

  try {
    std::string line;
    while (std::cin >> line) {
      std::cout << translator.Translate(line) << std::endl;
    }
  } catch (const std::exception &error) {
    std::cout << error.what() << std::endl;
  }
}

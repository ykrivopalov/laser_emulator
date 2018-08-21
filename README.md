# Laser emulator

Simple laser emulator.

## Implementation details

The main idea of this implementation is keep it simple and testable. There is no third-party dependencies except googletest for unit testing.

Implementation consist of:

* lib/ - static library with emulator core implementation. Splits on laser logic and protocol logic, both of them covered with tests.
* src/ - executable, that allows to operate the laser over stdin/stdout.
* test/ - unit tests

Some assumptions were made for places aren't covered in task description. For example:

* default power value
* KAL request for stopped laser

Emualation detalis:

* KeepAlive timer has 1s step


## Building

You need cmake >= 3.10 and compiler with C++14 support

```
mkdir build
cd build
cmake ..
make
```

To build in release mode, execute `cmake -DCMAKE_BUILD_TYPE=Release ..`.

To run tests, execute `make test`. Set `CTEST_OUTPUT_ON_FAILURE=1` for verbose output on failure.

To run emulator, execute `./src/laser_emulator`.

**!** Implementation is crossplatform, but it wasn't tested on Windows

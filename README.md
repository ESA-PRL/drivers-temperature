# Driver for temperature sensors

This library is used to read temperature sensors from a generic device. It can be used with any device and any number of temperature sensors as long as it complies with the protocol.

## Usage

The transmitted data protocol is the following:

| Item            | Byte numbers | Data type | Description                                               |
| --------------- | ------------ | --------- | --------------------------------------------------------- |
| Header          | 4            | `UINT8`   | Always `0xFE81FF55` (transmitted `0xFE` first)            |
| Sequence number | 1            | `UINT8`   | Increments for each message and resets to 0 after 127     |
| Message data    | 4\*sensors   | `SPFP`    | LSB output first, temperature value as sent by the device |

`SPFP` = Single Precision Floating Point (IEEE-754)  
`UINT8` = Unsigned 8-bit integer

## Unit test

A test script is under `src/main.cpp`. It is built and stored under `build/temperature_test`. To run it call the executable with the device as argument:

    sudo ./build/temperature_test /dev/ttyACMx

A dummy transmitter device example code can be found under `test/TemperatureTest`, the code is written for an Arduino Leonardo (the UNO resets itself at each start of a connection).


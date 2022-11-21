# Calibration Sensor Firmware for ESP32-WROOM-32

Calibration Sensor Firmware Project for ESP32 Module

# Docs

- [Core Library](main/core/README.md)

# Getting Started

1. Install `ESP-IDF` Framework version `4.4`.
2. On terminal, go to project root directory
3. Compile project by running `idf.py build`
4. Flash device by running `idf.py flash`

# ESP-IDF

This project make use of the ESP-IDF Framework. Module configurations can be accessed by running `idf.py menuconfig` on project root directory.

## Compiler configurations

Since ESP-IDF uses a component structure, it is required to add core library as a component.

The `CMakeLists.txt` file of the `main` component contain the compilation setup for the whole core library. The following variables CMake variables should be provided:

|        Macro        |          Description           |
| :-----------------: | :----------------------------: |
|   `include_dirs`    |     Project Include Paths      |
| `core_include_dirs` |   Core Library Include Paths   |
|       `srcs`        |      Project Source Files      |
|     `core_srcs`     |   Core Library Source Files    |
|   `dependencies`    | ESP-IDF Component Dependencies |







cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Set the project name
project(MotorControllerInterface)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include)

# Add the executable
add_executable(MotorControllerInterface
    src/main.cpp
    src/ControlInterface.cpp
    src/UARTProtocol.cpp
)

# Add the header files (optional, for IDEs)
set(HEADERS
    include/Commands.hpp
    include/ControlInterface.hpp
    include/Structs.hpp
    include/UARTProtocol.hpp
)

# Add the headers to the project (optional, for IDEs)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HEADERS})

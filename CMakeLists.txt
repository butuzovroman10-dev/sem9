cmake_minimum_required(VERSION 3.12)
project(CoinChange VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif()

# Основная программа
add_executable(coin_change
    src/main.cpp
    src/coin_change.cpp
    src/analysis.cpp
    tools/export_tools.cpp
)

target_include_directories(coin_change 
    PRIVATE 
        include
        tools
)

# Тесты
add_executable(test_coin_change
    tests/test_coin_change.cpp
    src/coin_change.cpp
    src/analysis.cpp
    tools/export_tools.cpp
)

target_include_directories(test_coin_change 
    PRIVATE 
        include
        tools
)

set_target_properties(coin_change test_coin_change
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
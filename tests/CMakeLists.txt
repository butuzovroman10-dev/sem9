# Исполняемый файл для тестов
add_executable(test_coin_change
    test_coin_change.cpp
)

# Связывание с основной библиотекой
target_link_libraries(test_coin_change
    PRIVATE 
        coin_change_lib
)

target_include_directories(test_coin_change 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
)

# Добавление тестов если включен CTest
if(BUILD_TESTING)
    enable_testing()
    add_test(NAME CoinChangeTests COMMAND test_coin_change)
endif()
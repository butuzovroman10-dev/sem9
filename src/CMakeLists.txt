# Основная исполняемая программа
add_executable(coin_change
    main.cpp
    coin_change.cpp
    analysis.cpp
)

# Установка путей для include файлов
target_include_directories(coin_change 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Установка свойств цели
set_target_properties(coin_change PROPERTIES
    OUTPUT_NAME "coin_change"
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

# Библиотека для тестов
add_library(coin_change_lib
    coin_change.cpp
    analysis.cpp
)

target_include_directories(coin_change_lib 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)

# Установка для установки
install(TARGETS coin_change
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
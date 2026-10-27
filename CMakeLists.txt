cmake_minimum_required(VERSION 3.28)
project(3DEngine_SFML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Подключение SFML через FetchContent ---
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        master # <-- ИЗМЕНЕНО
        CMAKE_ARGS     -DCMAKE_POLICY_VERSION_MINIMUM=3.22
)
FetchContent_MakeAvailable(SFML)

# --- Создаем цель (target) ---
add_executable(3DEngine_SFML src/main.cpp)

# --- Линкуем библиотеки ---
target_link_libraries(3DEngine_SFML PRIVATE SFML::Graphics SFML::Window SFML::System)
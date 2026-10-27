cmake_minimum_required(VERSION 3.28)
project(3DEngine_SFML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.1.0
)
FetchContent_MakeAvailable(SFML)

add_executable(3DEngine_SFML src/main.cpp)
target_link_libraries(3DEngine_SFML PRIVATE SFML::Graphics SFML::Window SFML::System)
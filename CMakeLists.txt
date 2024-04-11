cmake_minimum_required(VERSION 3.20)
project(LAB_9)

set(CMAKE_CXX_STANDARD 17)

add_executable(LAB_9 main.cpp)

include(FetchContent)

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(LAB_9 PRIVATE cpr::cpr)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(LAB_9 PRIVATE nlohmann_json::nlohmann_json)
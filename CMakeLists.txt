include(ExternalProject)

cmake_minimum_required(VERSION 3.0)

project(FarmerGame)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PUBLIC SDL2
    PUBLIC SDL2_image
)

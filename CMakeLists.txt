include(ExternalProject)

cmake_minimum_required(VERSION 3.0)

project(FarmerGame)

add_executable(${PROJECT_NAME} src/main.cpp)

# Build SDL2 lib
find_program(MAKE_EXECUTABLE NAMES gmake make mingw32-make REQUIRED)
execute_process(COMMAND ${MAKE_CMD} ${CMAKE_SOURCE_DIR}/external/sdl2 ${CMAKE_SOURCE_DIR}/lib/sdl2
    RESULT_VARIABLE CMD_ERROR
    # OUTPUT_FILE CMD_OUTPUT
)
message( STATUS "CMD_ERROR:" ${CMD_ERROR})
message( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})

# message(STATUS "sdl2_LIBRARY xxx${sdl2_LIBRARY}xxx")
message(STATUS "DIRECTORY = ${CMAKE_SOURCE_DIR}")

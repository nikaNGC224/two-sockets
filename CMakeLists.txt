cmake_minimum_required(VERSION 3.30)

project(two-sockets)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OUT_ARTIFACTS "${PROJECT_BINARY_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUT_ARTIFACTS}/bin/")

set(SERVER_MAIN src/server/main.cpp)
add_executable(server ${SERVER_MAIN})

set(CLIENT_MAIN src/client/main.cpp)
#set(CLIENT_SOURCES client/buffer.cpp client/functions.cpp)
#set(CLIENT_SOURCES client/client_app.hpp)
add_executable(client ${CLIENT_MAIN} ${CLIENT_SOURCES})
target_link_libraries(client pthread)


cmake_minimum_required(VERSION 3.11)

project(ima_cli CXX)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()
#some commit_
add_executable(ima_cli main.cpp TcpConnector.h TcpConnector.cpp)
target_include_directories(ima_cli PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(ima_cli ${SYSTEM_LIBS})

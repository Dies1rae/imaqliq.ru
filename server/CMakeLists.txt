cmake_minimum_required(VERSION 3.11)

project(imaqliq_server CXX)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

add_executable(ima_svc main.cpp TcpServer.h TcpServer.cpp)
target_include_directories(ima_svc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(ima_svc ${SYSTEM_LIBS})
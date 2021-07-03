cmake_minimum_required(VERSION 3.17)
project(pmbot)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -O3")
set(Boost_USE_MULTITHREADED ON)
add_subdirectory(SQLiteCpp)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(pmbot src/main.cpp src/blacklist/blacklist.cpp src/blacklist/blacklist.h src/utils/strtools.h src/utils/strtools.cpp)

target_link_libraries(pmbot /usr/local/lib/libTgBot.a
        ${CMAKE_THREAD_LIBS_INIT}
        ${OPENSSL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${CURL_LIBRARIES}
        SQLiteCpp)
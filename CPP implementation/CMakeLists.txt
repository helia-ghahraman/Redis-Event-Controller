#cmake_minimum_required(VERSION 3.1)
#project(RedisPubSubExample)
#
#set(CMAKE_CXX_STANDARD 11)
#
#find_library(CPP_REDIS_LIBRARY cpp_redis PATHS "/home/helia/cpp_redis/build/lib")
#
#
#include_directories(/home/helia/cpp_redis/includes)
#
#add_executable(server server.cpp)
#target_link_libraries(server PRIVATE ${CPP_REDIS_LIBRARY})
#
#add_executable(client client.cpp)
#target_link_libraries(client PRIVATE ${CPP_REDIS_LIBRARY})


cmake_minimum_required(VERSION 3.1)
project(RedisPubSubExample)

set(CMAKE_CXX_STANDARD 11)

# Assuming cpp_redis library is a submodule or available as a package
find_library(CPP_REDIS_LIBRARY cpp_redis)

# Include directories relative to the project's root directory
include_directories(${CMAKE_SOURCE_DIR}/cpp_redis/includes)

add_executable(server server.cpp)
target_link_libraries(server PRIVATE ${CPP_REDIS_LIBRARY})

add_executable(client client.cpp)
target_link_libraries(client PRIVATE ${CPP_REDIS_LIBRARY})

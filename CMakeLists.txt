cmake_minimum_required(VERSION 3.16)
project(banker C)

set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(banker banker.c process.c driver.c util.c)
target_link_libraries(banker PRIVATE Threads::Threads)

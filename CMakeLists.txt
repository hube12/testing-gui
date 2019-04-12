
cmake_minimum_required (VERSION 3.5)
project (imgui-glfw)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -static-libgcc -static-libstdc++ -static -pthread -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
set(CMAKE_BUILD_TYPE Release)

add_definitions("-DCPP_SRC_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\"")


add_subdirectory(modules)
add_subdirectory(src)


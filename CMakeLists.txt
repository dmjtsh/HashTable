cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hash_table VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp DimasLIB/DimasList/*cpp DimasLIB/DimasHash/*.cpp DimasLIB/DimasTextInfo/*.cpp DimasLIB/DimasUtilities/*.cpp)
add_executable(hash_table main.cpp ${SRC_FILES})

target_include_directories(hash_table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(hash_table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DimasLIB/DimasList)
target_include_directories(hash_table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DimasLIB/DimasHash)
target_include_directories(hash_table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DimasLIB/DimasTextInfo)

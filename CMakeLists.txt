cmake_minimum_required(VERSION 3.20)

project(rush VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-DLOG_USE_BUILDER -DLOG_USE_COLOR")

# find libraries
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
endif ()

# collect all executables
set(RUSH_ENTITY
    src/entity/camera.cpp
    src/entity/entity.cpp
)
set(RUSH_CORE
    # src/core/
)
set(RUSH_UTIL
    src/util/log.c
    src/util/shader_loader.cpp
    src/util/resource_loader.cpp
)
set(SOURCES
    ${RUSH_ENTITY}
    # ${RUSH_CORE}
    ${RUSH_UTIL}
    src/main.cpp
)

add_executable(rush ${SOURCES})

# collect all headers
target_include_directories(rush PUBLIC
    include
    lib
)
target_link_libraries(rush PRIVATE
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    glfw
)
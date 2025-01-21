cmake_minimum_required(VERSION 3.20)

project(rush VERSION 0.1.7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-DLOG_USE_BUILDER -DLOG_USE_COLOR")

# find libraries
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
endif ()

# collect all executables
set(RUSH_CORE
    src/core/renderer.cpp
    src/core/scene.cpp
    src/core/shader.cpp
)
set(RUSH_ENTITY
    src/entity/camera.cpp
    src/entity/entity.cpp
    src/entity/mesh.cpp
    src/entity/object.cpp
)
set(RUSH_UTIL
    src/util/log.c
    src/util/resource_loader.cpp
    src/util/shader_loader.cpp
)
set(RUSH_WORLD
    src/world/grid.cpp
    src/world/terrain.cpp
)
set(SOURCES
    ${RUSH_ENTITY}
    ${RUSH_CORE}
    ${RUSH_UTIL}
    ${RUSH_WORLD}
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
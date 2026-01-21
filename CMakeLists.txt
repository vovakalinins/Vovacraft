cmake_minimum_required(VERSION 3.23)
project(Vovacraft)

#C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

set(SOURCES 
    src/main.cpp 
    src/glad.c
    src/graphics/mesh.cpp
    src/graphics/texture.cpp
    include/graphics/camera.h
    include/core/GameState.h
    src/core/GameState.cpp
    include/core/input.h
    src/core/input.cpp
    src/world/chunk.cpp
    include/world/chunk.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    include 
    ${GLFW_INCLUDE_DIRS}
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        glfw 
        "-framework OpenGL" 
        "-framework Cocoa" 
        "-framework IOKit" 
        "-framework CoreVideo" 
        "-framework CoreFoundation"
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" 
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
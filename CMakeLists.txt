cmake_minimum_required(VERSION 3.16.3)
set(PROJECT_NAME Sokoban3D)
project(${PROJECT_NAME})

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

function(watch)
    set_property(
            DIRECTORY
            APPEND
            PROPERTY CMAKE_CONFIGURE_DEPENDS ${ARGV}
    )
endfunction()

set(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
set(CMAKE_CXX_STANDARD 14)

#--coverage
list(APPEND CMAKE_CXX_FLAGS "-g -Wall -Wextra")

file(GLOB SOURCES "src/*.cpp" "src/*.c" src/main.cpp)
file(GLOB HEADERS "include/*.h" "include/*.hpp")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(ASSIMP REQUIRED)

#if(CMAKE_COMPILER_IS_GNUCXX)
#    include(CodeCoverage)
#    append_coverage_compiler_flags()
#
#    SETUP_TARGET_FOR_COVERAGE_LCOV(NAME coverage EXECUTABLE ${PROJECT_NAME})
#endif()

add_subdirectory(libs/glad)
add_definitions(${OPENGL_DEFINITIONS})

add_library(STB_IMAGE libs/stb_image.cpp)
set(LIBS glfw glad OpenGL::GL X11 Xrandr Xinerama Xi Xxf86vm Xcursor dl pthread freetype ${ASSIMP_LIBRARIES} STB_IMAGE)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

include_directories(include/)
add_executable(${PROJECT_NAME}
        ${SOURCES})


target_link_libraries(${PROJECT_NAME} ${LIBS})

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
file(GLOB SHADERS "shaders/*.vs"
        "shaders/*.fs")
foreach(SHADER ${SHADERS})
    # file(COPY ${SHADER} DESTINATION ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/shaders)
    watch(${SHADER})
endforeach()


cmake_minimum_required(VERSION 3.16.3)
project(interactive-point-cloud)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(CMAKE_COMPILER_IS_GNUCXX OR(CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-deprecated-declarations -O3 -funroll-loops -g")

    if(MESHVIEW_USE_FFAST_MATH)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
    endif()
elseif(MSVC)
    if(MESHVIEW_USE_FFAST_MATH)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
    endif()

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /GLT /Ox")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT /GLT")

    # silence deprecation warning coming from Eigen; silence secure warning
    add_definitions(-D_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING -D_CRT_SECURE_NO_WARNINGS)
endif()

# ImGui
file(GLOB IMGUI_SOURCES
    thirdparty/imgui/*.cpp
    thirdparty/imgui/examples/imgui_impl_glfw.cpp
    thirdparty/imgui/examples/imgui_impl_opengl3.cpp)
file(GLOB IMGUI_HEADERS thirdparty/imgui/*.h)
set(IMGUI_DIR
    thirdparty/imgui
    thirdparty/imgui/examples)
add_library(imgui STATIC
    ${IMGUI_SOURCES})
include_directories(
    ${IMGUI_DIR})

# imgui-filebrowser
file(GLOB IMGUI_FILEBROWSER_HEADERS
    thirdparty/imgui-filebrowser/*.h)
set(IMGUI_FILE_BROWSER_DIR
    thirdparty/imgui-filebrowser)
include_directories(
    ${IMGUI_FILE_BROWSER_DIR})

# guik from interactive_slam
find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PCL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB INTERACTIVE_SLAM_SOURCES
    thirdparty/interactive_slam/gl3w/*.c
    thirdparty/interactive_slam/glk/*.cpp
    thirdparty/interactive_slam/glk/loaders/*.cpp
    thirdparty/interactive_slam/glk/primitives/*.cpp
    thirdparty/interactive_slam/guik/*.cpp)
file(GLOB INTERACTIVE_SLAM_HEADERS
    thirdparty/interactive_slam/glk/*.h
    thirdparty/interactive_slam/glk/loaders/*.h
    thirdparty/interactive_slam/glk/primitives/*.h
    thirdparty/interactive_slam/guik/*.h
    thirdparty/interactive_slam/gl3w/GL/gl3w.h)
set(INTERACTIVE_SLAM_DIR
    thirdparty/interactive_slam
    thirdparty/interactive_slam/gl3w)

set(INTERACTIVE_SLAM_SHADER_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/interactive_slam/shaders")
configure_file(config/shaders.h.in shaders.h @ONLY)

add_library(interactive_slam STATIC
    ${INTERACTIVE_SLAM_SOURCES})
target_link_libraries(interactive_slam
    ${OPENGL_LIBRARIES}
    Eigen3::Eigen
    ${EIGEN_}
    ${glfw3_LIBRARIES}
    ${PCL_LIBRARIES}
    imgui;glfw;GLEW;GL)
include_directories(
    ${INTERACTIVE_SLAM_DIR}
    ${Eigen3_INCLUDE_DIR}
    ${IMGUI_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${PCL_INCLUDE_DIRS})

# interative-point-cloud
file(GLOB GL_SOURCES src/gl/*.cpp)
file(GLOB UI_SOURCES src/ui/*.cpp)
file(GLOB APP_SOURCES
    src/interactive_point_cloud.cpp
    src/interactive_point_cloud_application.cpp)

add_executable(interative_point_cloud
    ${GL_SOURCES}
    ${UI_SOURCES}
    ${APP_SOURCES})
target_link_libraries(interative_point_cloud
    imgui
    interactive_slam)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR})

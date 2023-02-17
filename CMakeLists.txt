cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

# add_executable(main main.cpp)

####
# 使用C++ 11标准
set(CMAKE_CXX_STANDARD 11)

## 添加头文件
set(GLFW_H /usr/local/include)
set(GLAD_H ${PROJECT_SOURCE_DIR}/include)
include_directories(${GLAD_H} ${GLFW_H})


##添加目标链接
set(GLFW_LINK /usr/local/lib/libglfw.3.dylib)
link_libraries(${GLFW_LINK})

## 执行编译命令
set(SOURCES glad.c main.cpp)

add_executable(main ${SOURCES})

## 链接系统的OpenGL 框架
if (APPLE)
    target_link_libraries(main "-framework OpenGL")
endif()

include(CTest)
enable_testing()



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

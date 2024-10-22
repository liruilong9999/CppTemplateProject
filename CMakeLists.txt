# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.12)

# 设置项目名称
project(CppTemplateProject)

# C++标准
add_compile_options(/std:c++14)

# 使用 UTF-8 编码
if(MSVC)
    add_compile_options(/utf-8)  # 强制 VS 使用 UTF-8
endif()

# 开启使用文件夹功能，将所有默认目标放入到名为 CMakePredefinedTargets 的文件夹中
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTargets")

# 设置根目录
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${ROOT_DIR}/build)

# 添加子目录，子目录下必须有CMakeLists.txt
add_subdirectory(src)
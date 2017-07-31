# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (CatoolDemo)
# 添加头文件
include_directories(../Catool)
# 指定生成目标
add_executable(CatoolDemo test.cpp)

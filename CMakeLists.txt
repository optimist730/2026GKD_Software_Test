cmake_minimum_required(VERSION 3.10)
project("实时传感器流水线")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(action 
src/main.cpp 
src/SeneorTask.cpp 
src/Taskmanager.cpp )
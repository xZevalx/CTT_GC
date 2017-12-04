cmake_minimum_required(VERSION 3.8)
project(CTTtoGVC)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp Graph/Node.cpp Graph/Node.h Colour/Colour.cpp Colour/Colour.h CTT/Course.cpp
        CTT/Course.h Graph/Graph.cpp Graph/Graph.h Colour/Palette.cpp Colour/Palette.h CTT/Room.h CTT/Room.cpp
        CTT/Curricula.cpp CTT/Curricula.h ctt_reader.h ctt_reader.cpp Scheduler/scheduler.h Scheduler/scheduler.cpp)
add_executable(CTTtoGVC ${SOURCE_FILES})
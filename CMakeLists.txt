cmake_minimum_required(VERSION 3.19)
project(SP_4b)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SP_4b
        Board.cpp
        Board.hpp
        City.hpp
        Color.hpp
        Demo1.cpp
        #        Demo2.cpp
        Dispatcher.cpp
        Dispatcher.hpp
        FieldDoctor.cpp
        FieldDoctor.hpp
        GeneSplicer.cpp
        GeneSplicer.hpp
        Medic.cpp
        Medic.hpp
        OperationsExpert.cpp
        OperationsExpert.hpp
        Player.cpp
        Player.hpp
        Researcher.cpp
        Researcher.hpp
        Scientist.cpp
        Scientist.hpp
        #        TestCounter.cpp
        Virologist.cpp
        Virologist.hpp)
cmake_minimum_required(VERSION 3.7...3.23)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Polylla-Matlab VERSION 1.0
                  DESCRIPTION "Matlab interface for Polylla"
                  LANGUAGES CXX)

find_package(Matlab)
matlab_add_mex(NAME Polylla SRC "src/Polylla.cpp")
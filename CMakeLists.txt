cmake_minimum_required(VERSION 3.7...3.23)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Polylla-Matlab VERSION 1.0
                  DESCRIPTION "Matlab interface for Polylla"
                  LANGUAGES CXX)


add_subdirectory(extern/Polylla)
set(POLYLLA_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/extern/Polylla/include)

find_package(Matlab)
matlab_add_mex(
    NAME Polylla-Matlab
    SRC "src/Polylla.cpp"
    OUTPUT_NAME useCPPPolylla
    LINK_TO meshfiles
)

target_include_directories(Polylla-Matlab
    PUBLIC ${POLYLLA_INCLUDE}
)
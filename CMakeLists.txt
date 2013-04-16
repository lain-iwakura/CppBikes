cmake_minimum_required (VERSION 2.8)

project(Bikes)

if(MSVC)
	add_definitions(/W3)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -pedantic)
else()
	message("Unknown compiler")
endif()

set(CMAKE_USE_RELATIVE_PATHS true)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

file(GLOB BIKES_HEADERS "include/Bikes/*.h")
file(GLOB BIKES_SOURCES "src/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Bikes ${BIKES_HEADERS} ${BIKES_SOURCES})
set_target_properties(Bikes PROPERTIES DEBUG_POSTFIX "_d")

include_directories(${BIKES_SOURCE_DIR})

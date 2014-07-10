cmake_minimum_required(VERSION 2.8)

set(target_name cvcap)
set(src main.cpp)

set(CMAKE_CXX_FLAGS "-Wall -g")
set(CMAKE_C_FLAGS "-Wall -g")

project( ${target_name} )

find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED COMPONENTS program_options-mt)

include_directories( /usr/local/include ${OpenCV_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} )

add_executable(${target_name} ${src})
target_link_libraries(${target_name} ${OpenCV_LIBS} ${Boost_LIBRARIES} )
install(TARGETS ${target_name} RUNTIME DESTINATION bin)

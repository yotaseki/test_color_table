project(make_color_table)
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(make_color_table
    ../../../detector/color_table.h
    ../../../detector/convert_color.h
    ../../../detector/color_table.cpp
    ../../../detector/convert_color.cpp
    make_color_table.cpp
)

target_link_libraries(make_color_table
    ${OpenCV_LIBS}
)

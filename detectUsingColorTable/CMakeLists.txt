project(detectUsingColorTable)
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem)
IF(WIN32)
    set(Boost_USE_STATIC_LIBS        ON)
ELSE(WIN32)
    set(Boost_USE_STATIC_LIBS       OFF)
ENDIF(WIN32)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
include_directories(
    ${OpenCV_INCLUDE_DIRS}
	${BOOST_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
    )
link_directories(
	${Boost_LIBRARY_DIRS}
	${Boost_LIBRARY_DIR}
)
add_executable(detectUsingColorTable
    ../../detector/color_table.h
    ../../detector/convert_color.h
    ../../detector/color_table.cpp
    ../../detector/convert_color.cpp
    detectUsingColorTable.cpp
)
target_link_libraries(detectUsingColorTable
    ${OpenCV_LIBS}
	${Boost_LIBRARIES}
)

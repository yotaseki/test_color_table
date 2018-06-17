project(test)
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(test_fcn
    main.cpp
    test.h
    test.cpp
)
target_link_libraries(test
    ${OpenCV_LIBS}
)

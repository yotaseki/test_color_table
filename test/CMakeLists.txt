project(test)
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS date_time system filesystem)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
include_directories(
    ${OpenCV_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)
add_executable(test
    main.cpp
    test.h
    test.cpp
    rcsv.h
    rcsv.cpp
    getFilename.h
    getFilename.cpp
)
target_link_libraries(test
	${Boost_LIBRARIES}
    ${OpenCV_LIBS}
)
add_executable(getImage
    getImage.cpp
    test.h
    test.cpp
    rcsv.h
    rcsv.cpp
    getFilename.h
    getFilename.cpp
)
target_link_libraries(getImage
	${Boost_LIBRARIES}
    ${OpenCV_LIBS}
)

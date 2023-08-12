cmake_minimum_required(VERSION 3.5)
project(image_resizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV 4 REQUIRED)
find_package(Boost COMPONENTS context fiber date_time url REQUIRED)
find_package(libasyik)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

set(COMMON_INCLUDE_DIRS include ${OpenCV_INCLUDE_DIRS})
set(COMMON_LIBRARIES
    ${OpenCV_LIBS}
    Boost::fiber
    Boost::context
    ${JSONCPP_LINK_LIBRARIES}
    Threads::Threads
    OpenSSL::SSL)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(image_resizer_lib ${SOURCES})
target_include_directories(image_resizer_lib PUBLIC ${COMMON_INCLUDE_DIRS})
target_link_libraries(image_resizer_lib PUBLIC ${COMMON_LIBRARIES} libasyik)

add_library(image_resizer_shared_lib "src/base64.cpp" "src/image_processing.cpp" "src/json_handler.cpp")
target_include_directories(image_resizer_shared_lib PUBLIC ${COMMON_INCLUDE_DIRS})
target_link_libraries(image_resizer_shared_lib PUBLIC ${COMMON_LIBRARIES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} image_resizer_lib)

add_subdirectory(external/catch2)
enable_testing ()
add_subdirectory(tests)

project(image_resizer_test)

add_executable(${PROJECT_NAME} image_processing_test.cpp base64_test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE image_resizer_shared_lib Catch2::Catch2WithMain)

add_test (NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
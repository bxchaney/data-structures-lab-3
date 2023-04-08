add_library(encoding encoder.cpp decoder.cpp)
add_subdirectory(utils)

target_include_directories(encoding INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(encoding PUBLIC utils)
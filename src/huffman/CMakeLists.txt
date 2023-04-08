add_library(huffman huffman.cpp freq_table.cpp)
# add_library(freq_table freq_table.cpp)
target_include_directories(huffman INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(freq_table INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
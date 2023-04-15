add_library(utils tree_map.cpp freq_table.cpp huffman.cpp huff_tree.cpp code_table.cpp)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
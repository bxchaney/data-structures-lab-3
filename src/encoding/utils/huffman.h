#pragma once
#include<memory>
#include<string>
#include"huff_tree.h"
#include"freq_table.h"



class Huffman 
{
    private:
        std::unique_ptr<HuffTree[]> huff_heap;
        int _heap_size;        
        int _heap_max_size;

        void percolate_down();
        void percolate_up();
        HuffTree& pop();
        void push(HuffTree&);

    public:
        Huffman() = default;
        Huffman(FrequencyTable);
        ~Huffman();
        
        bool is_character(std::string);
        std::string get_character(std::string);

        std::string get_code(std::string);
};
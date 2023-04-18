/**
 * Huffman contains the priority queue that constructs our huffman tree
 * and contains a number of utility objects as class members. This object
 * is the main utility for the Encoder and Decoder abstractions and provides
 * wrapper methods to allow those abstractions access to the members of this
 * class.
 * 
 */

#pragma once
#include<iostream>
#include<memory>
#include<string>
#include"huff_tree.h"
#include"freq_table.h"
#include"code_table.h"

class Huffman 
{
    private:
        std::unique_ptr<HuffTree[]> huff_heap;
        int _heap_size;        
        int _heap_max_size;

        std::unique_ptr<std::string[]> characters;

        EncodingTable code_table;

        void heapify();
        void min_heapify(int);
        void swap(int, int);

        void percolate_down(int);
        void percolate_up(int);
        HuffTree pop();
        void push(HuffTree&);
        void create_huff_tree();


    public:
        Huffman() = default;
        Huffman(FrequencyTable);
        ~Huffman() = default;
        
        void from_freq(FrequencyTable);

        bool is_character_encoding(std::string&);
        std::string& get_character(std::string&);

        std::string get_code(std::string);

        EncodingTable& get_encoding_table();

        HuffTree& get_tree();

        friend std::ostream& operator<<(std::ostream&, Huffman&);
};
#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"utils/huffman.h"
#include"utils/freq_table.h"
#include"utils/tree_map.h"
#include"code_table.h"

class Encoder
{
    private:
        FrequencyTable ft;
        Huffman huff;
        bool _freq_table_provided;
        TreeMap tree_map;

        std::stringstream encoded_message {};

        std::stringstream s_stream {};

        void write_encoding();
        void write_encoding(std::istream&);
        void make_encoding(std::istream&);

    public:
        Encoder() = default;
        Encoder(FrequencyTable&);

        ~Encoder() = default;

        void encode(std::istream&);

        FrequencyTable& get_frequency_table();
        EncodingTable& get_code_table();
        HuffTree& get_tree() { return huff.get_tree();}


        friend std::ostream& operator<<(std::ostream&, Encoder&);
};
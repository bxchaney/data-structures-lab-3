#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<memory>
#include"utils/freq_table.h"
#include"utils/huffman.h"
#include"utils/code_table.h"

class Decoder
{
    private:

        FrequencyTable ft;
        Huffman huff;

        std::stringstream decoded_message;

    public:
        Decoder() = default;
        Decoder(std::istream&);
        ~Decoder() = default;

        void decode(std::istream&);

        FrequencyTable& get_freq_table();

        EncodingTable get_code_table();

        friend std::ostream& operator<<(std::ostream&, Decoder&);

};
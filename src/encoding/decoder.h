#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<memory>
#include"utils/freq_table.h"
#include"utils/huffman.h"
#include"utils/code_table.h"

class Decoder
{
    private:

        FrequencyTable ft;
        Huffman huff;

        std::filebuf buffer;
        std::ostream decoded_message {&buffer};

    public:
        Decoder() = default;
        Decoder(std::istream&);
        ~Decoder() = default;

        void decode(std::istream&);

        FrequencyTable& get_freq_table();

        EncodingTable get_code_table();

        friend std::ostream& operator<<(std::ostream&, Decoder&);

};
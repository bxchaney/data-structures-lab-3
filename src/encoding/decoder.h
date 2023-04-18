/**
 * Decoder is the ADT used to decode a huffman-encoded document. It can be
 * initialized with a FrequencyTable object and then you can have a message
 * decoded by passing a std::istream to the decode() method.
 * 
 */

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

        EncodingTable& get_code_table();

        /// @brief returns a referece to the huffman tree used to decode
        /// the message
        /// @return 
        HuffTree& get_tree(){return huff.get_tree();}

        friend std::ostream& operator<<(std::ostream&, Decoder&);

};
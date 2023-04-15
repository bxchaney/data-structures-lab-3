#include<iostream>
#include<string>
#include<fstream>
#include"decoder.h"
#include"utils/freq_table.h"
#include"utils/huffman.h"
#include"utils/code_table.h"

Decoder::Decoder(std::istream& freq_table)
{
    ft = FrequencyTable{freq_table};
    huff.from_freq(ft);
}

void Decoder::decode(std::istream& is)
{
    // we assume that the encoded message is only 0's, 1's, and newlines
    std::string s;
    char c;
    while ((c = is.get()) != EOF)
    {
        if (c == '\n')
        {
            if( s != "" && s != "\r") { std::cout << "uh oh: |" << s << "|"<< std::endl;}
            decoded_message << std::endl;
            s = "";
            continue;
        }
        s = s + c;
        if (huff.is_character_encoding(s))
        {
            std::string x = huff.get_character(s);
            decoded_message << x;
            s = "";
        }
    }
}

FrequencyTable& Decoder::get_freq_table()
{
    return ft;
}

EncodingTable Decoder::get_code_table()
{
    return huff.get_encoding_table();
}

std::ostream& operator<<(std::ostream& os, Decoder& dec)
{
    os << dec.decoded_message.rdbuf();
    return os;
}
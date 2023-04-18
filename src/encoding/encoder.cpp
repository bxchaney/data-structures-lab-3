#include<iostream>
#include<fstream>
#include<string>
#include"utils/freq_table.h"
#include"utils/tree_map.h"
#include"utils/huffman.h"
#include"code_table.h"
#include"encoder.h"

/// @brief overload to allow the user to provide a frequency table. If a
/// frequency table is not provided at initialization, Encoder will create
/// a frequency table from the clear text file.
/// @param ft 
Encoder::Encoder(FrequencyTable& ft)
{
    this->ft = ft;
    _freq_table_provided = true;
    huff.from_freq(ft);
}

/// @brief Converts the provided clear text document to an encoded document
/// @param is 
void Encoder::encode(std::istream& is)
{
    if (!_freq_table_provided)
    {
        make_encoding(is);
        write_encoding();
    }
    write_encoding(is);
}

/// @brief this method is only called if the user does not provide a frequency
/// table. This method builds a frequency table and its corresponding huffman tree
/// @param is 
void Encoder::make_encoding(std::istream& is)
{
    std::string s;
    while (!is.eof())
    {
        s = is.get();
        if (s == "\n")
        {
            s_stream << "\n";
        }
        else if (s == "\r" || s > "z")
        {
            continue;
        }
        else
        {
            tree_map[s]++;
            s_stream << s;
        }
    }
    tree_map.fill_freq_table(ft);
    huff.from_freq(ft);
}

/// @brief This method writes the encoded mesage to encoded_message
void Encoder::write_encoding()
{
    // case when freq table is not provided
    std::string s;
    while (s_stream)
    {
        s = s_stream.get();
        if (s == "\n")
        {
            encoded_message << "\n";
        }
        else if (s == "\r" || s > "z")
        {
            continue;
        }
        else 
        {
            encoded_message << huff.get_code(s);
        }
    }
}

/// @brief This method writes the encoded mesage to encoded_message
void Encoder::write_encoding(std::istream& is)
{
    char c;
    std::string s;
    while (!is.eof())
    {
        c = is.get();
        if (c == '\n')
        {
            encoded_message << std::endl;
            continue;
        }
        // ignoring punctuation
        else if (
            c == '\r' 
            || c == '.'
            || c == '!'
            || c == ','
            || c == '\''
            || c == '?'
            || c == ' '
            || c == '-'
            )
        {
            continue;
        }
        else if 
            (
                c >= 'a' && c <= 'z'
            )
        {
            // converting to uppercase
            s = c - 32;
        }
        else 
        {
            s = c;
        }
        encoded_message << huff.get_code(s);
    }
}

/// @brief returns a reference to the member FrequencyTable
/// @return 
FrequencyTable& Encoder::get_frequency_table()
{
    return ft;
}

/// @brief returns the EncodingTable stored in the member Huffman
/// @return 
EncodingTable& Encoder::get_code_table()
{
    return huff.get_encoding_table();
}

std::ostream& operator<<(std::ostream& os, Encoder& en)
{
    os << en.encoded_message.rdbuf();
    return os;
}

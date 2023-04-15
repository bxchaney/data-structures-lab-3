#include<iostream>
#include<fstream>
#include<string>
#include"utils/freq_table.h"
#include"utils/tree_map.h"
#include"utils/huffman.h"
#include"encoder.h"

Encoder::Encoder(FrequencyTable& ft)
{
    this->ft = ft;
    _freq_table_provided = true;
    huff.from_freq(ft);
}

void Encoder::encode(std::istream& is)
{
    if (!_freq_table_provided)
    {
        make_encoding(is);
        write_encoding();
    }
    write_encoding(is);
}

void Encoder::make_encoding(std::istream& is)
{
    std::string s;
    while (!is.eof())
    {
        s = is.get();
        if (s == "\n")
        {
            s_stream << std::endl;
        }
        else if (s == "\r")
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

void Encoder::write_encoding()
{
    // case when freq table is not provided
    std::string s;
    while (s_stream)
    {
        s_stream >> s;
        if (s == "\n")
        {
            encoded_message << std::endl;
        }
        else if (s == "\r")
        {
            continue;
        }
        else 
        {
            encoded_message << huff.get_code(s);
        }
    }
}

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
            s = c + 32;
        }
        else 
        {
            s = c;
        }
        encoded_message << huff.get_code(s);
    }
}

std::ostream& operator<<(std::ostream& os, Encoder& en)
{
    os << en.encoded_message.rdbuf();
    return os;
}

#include<iostream>
#include<memory>
#include<string>
#include<fstream>
#include"encoding/decoder.h"
#include"encoding/utils/code_table.h"


int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        std::filebuf fb_freq_table;
        std::filebuf fb_message;
        if (!fb_freq_table.open(argv[1], std::ios::in))
        {
        std::cout << "Problem opening frequency table!" << std::endl;
        return -1;
        }

        if (!fb_message.open(argv[2], std::ios::in))
        {
            std::cout << "Problem opening message!" << std::endl;
            return -1;
        }

        std::istream is_freq_table {&fb_freq_table};
        std::istream is_message {&fb_message};

        Decoder dec {is_freq_table};

        // std::cout << dec.get_freq_table() << std::endl;

        dec.decode(is_message);

        EncodingTable et = dec.get_code_table();
        std::cout << et << std::endl;
        // std::cout << "lol" << std::endl;
        std::cout << dec << std::endl;
        return 0;
    }


    
    

}
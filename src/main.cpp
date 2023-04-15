#include<iostream>
#include<memory>
#include<string>
#include<fstream>
#include<sstream>
#include"encoding/decoder.h"
#include"encoding/utils/code_table.h"


int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        std::string flag = argv[1];
        
        // decode a message
        // assumes the user provides a frequency table, encoded message, and
        // output filename, in that order
        if (flag == "-d")
        {
            if (argc < 5)
            {
                std::cout << "Not enough arguments provided for decoding. ";
                std::cout << "Expecting to recieve a frequency table, ";
                std::cout << "encoded message, and an output filename";
            }
            
            std::filebuf fb_freq_table;
            std::filebuf fb_message;
            std::filebuf fb_output;

            if (!fb_freq_table.open(argv[2], std::ios::in))
            {
                std::cout << "Problem opening frequency table!" << std::endl;
                fb_freq_table.close();
                return -1;
            }
            if (!fb_message.open(argv[3], std::ios::in))
            {
                std::cout << "Problem opening message file!" << std::endl;
                fb_message.close();
                return -1;
            }
            if (!fb_output.open(argv[4], std::ios::out))
            {
                std::cout << "Problem opening output file!" << std::endl;
                fb_output.close();
                return -1;
            }

            std::istream in_freq {&fb_freq_table};
            std::istream in_mesg {&fb_message};

            std::ostream out_mesg {&fb_output};

            Decoder dec {in_freq};
            dec.decode(in_mesg);

            // std::cout << dec << std::endl;
            out_mesg << dec;
            std::cout << "Successfully decoded message!" << std::endl;
            fb_output.close();
        }
    }
   

}
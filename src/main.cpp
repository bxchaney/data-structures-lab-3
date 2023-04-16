#include<iostream>
#include<memory>
#include<string>
#include<fstream>
#include<sstream>
#include"encoding/decoder.h"
#include"encoding/encoder.h"
#include"encoding/utils/freq_table.h"


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
        else if (flag == "-e")
        {
            // assuming if -e flag then the next arg is the file to be encoded
            if (argc == 3)
            {
                std::string source_file = argv[2];
                std::string freq_file = "frequency_table_" + source_file;
                std::string codes = "codes_" + source_file;
                std::string encoded_string = "encoded_" + source_file;

                Encoder en {};

                std::filebuf fb_in;
                std::filebuf fb_freq_file;
                std::filebuf fb_code_file;
                std::filebuf fb_encoded_file;

                if (!fb_in.open(source_file, std::ios::in))
                {
                    std::cout << "Problem opening source file!" << std::endl;
                    return -1;
                }
                fb_freq_file.open(freq_file, std::ios::out);
                fb_code_file.open(codes, std::ios::out);
                fb_encoded_file.open(encoded_string, std::ios::out);
                
                std::istream is {&fb_in};

                en.encode(is);

                std::ostream os_freq {&fb_freq_file};
                std::ostream os_code {&fb_code_file};
                std::ostream os_encoded_file {&fb_encoded_file};

                os_freq << en.get_frequency_table();
                os_code << en.get_code_table();
                os_encoded_file << en;

                fb_in.close();
                fb_freq_file.close();
                fb_code_file.close();
                fb_encoded_file.close();


            }
            else if (argc == 4)
            {
                // when -e flag and 4 args, expecting to recieve a freq table
                // and the message to be encoded.
                
                std::filebuf fb_freq;
                std::filebuf fb_msg;
                std::filebuf fb_codes;
                std::filebuf fb_coded_msg;

                std::string message_file = argv[3];

                if (!fb_freq.open(argv[2], std::ios::in))
                {
                    std::cout << "Problem opening frequency table!" << std::endl;
                    return -1;
                }
                if (!fb_msg.open(message_file, std::ios::in))
                {
                    std::cout << "Problem opening message file!" << std::endl;
                    return -1;
                }


                std::string codes_str = "codes_" + message_file;
                std::string encoded_message = "encoded_" + message_file;

                fb_codes.open(codes_str, std::ios::out);
                fb_coded_msg.open(encoded_message, std::ios::out);

                std::istream freq_stream {&fb_freq};
                std::istream msg_stream {&fb_msg};
                
                FrequencyTable ft {freq_stream};

                Encoder en {ft};

                en.encode(msg_stream);

                std::ostream codes {&fb_codes};
                std::ostream out_msg {&fb_coded_msg};

                codes << en.get_code_table();
                out_msg << en;
                
                fb_freq.close();
                fb_msg.close();
                fb_codes.close();
                fb_coded_msg.close();

            }
            else
            {
                return -1;
            }
            std::cout << "Successfully encoded message!" << std::endl;

        }
        else 
        {
            std::cout << "Invalid second argument, expecting either '-d' for ";
            std::cout << "decoding, or '-e' for encoding." << std::endl;
            return -1;
        }
    }
   

}
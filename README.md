# ChaneyBLab3

## Lab 3

The assignment is to implement a Huffman encoding and decoding. Given an encoded document and a frequency table, the program is able to decode the document. Given an unencoded document, the program will create a frequency table if one is not already provided, and then store an encoded version of the document.

## Configuration Info

Operating System: Ubuntu 22.04

C++ Compiler: g++ 11.3.0

IDE: Visual Studio Code version 1.75.1 with the most recent version of the C/C++ extension pack.

Build System: CMake 3.22.1

I have included my compiled executable in the top directory of this zip, it will not be overwritten when you build from source using CMake

## How to Build

- Assuming the user has access to a Unix-like system with CMake installed.
- From the zip directory, execute the following commands:

```
mkdir build
cd build
cmake ../src
cmake --build .
cd ..
```

- The compiled executable should now be ready at ./build/Lab3 !

## How to Run

- Once the executable is built we can run the required input by calling `./build/apps/Lab3 -d FreqTable.txt Encoded.txt Out.txt` from the command line. `Out.txt` will have the decoded output from the program in this case, the chose of output name is left to the user. In general, we can decode files by calling `./build/Lab3 -d [frequency table file] [encoded file] [output file name]`.
- To encode a message, run `./build/Lab3 -e FreqTable.txt ClearText.txt`. This will save the character huffman codes to `codes_ClearText.txt`, and the encoded message to `encoded_ClearText.txt`. If you then want to decode that message, call `./build/Lab3 -d FreqTable.txt encoded_ClearText.txt out_ClearText.txt`. The decoded result will be saved to `out_ClearText.txt`
- This program also allows the user to encode a message without having a frequency table provided. In this case, you call `./build/Lab3 -e [filename.txt]` and the encoding table will be saved to `codes_[filename.txt]`, the frequency table will be saved to `frequency_table_[filename.txt]` and the encoded output will be saved to `encoded_[filename.txt]`. You can then decode this message in the same way as the first bullet. As an example, I have included `frankenstein.txt`, the entire text of the novel _Frankenstein or, the Modern Prometheus_ by Mary Shelly (used with permission under the Gutenberg License), as the example text I used to create a new encoding. If you use this method, the program also encodes lowercase letters, punctuation and whitespace characters, allowing for minimal loss when decoding!

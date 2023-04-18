/**
 * Encoding Table is a singly-linked list used to store the character its
 * huffman code. This object supports adding new elements to the list and
 * has overloaded the << operator to allow writing its contents directly
 * to a std::ostream
 * 
 */

#pragma once 
#include<iostream>
#include<string>
#include<memory>

struct Encoding
{
    std::string character;
    std::string encoding;
};

class EncodingTable
{

    private:
        struct EncodingNode
        {
            std::shared_ptr<EncodingNode> next;

            Encoding code;

            EncodingNode() = default;
            EncodingNode(Encoding&);
            ~EncodingNode() = default;
        };

        std::shared_ptr<EncodingNode> _head;
        std::shared_ptr<EncodingNode> _tail;

    public:
        EncodingTable() = default;
        EncodingTable(const EncodingTable&);
        EncodingTable& operator=(const EncodingTable&);
        ~EncodingTable();
        
        void push(std::string, std::string);

        friend std::ostream& operator<<(std::ostream&, EncodingTable&);

};
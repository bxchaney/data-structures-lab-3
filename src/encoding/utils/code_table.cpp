#include<iostream>
#include<string>
#include<memory>
#include"code_table.h"

EncodingTable::EncodingNode::EncodingNode(Encoding& code)
{
    this->code = code;
    next = nullptr;
}

EncodingTable::EncodingTable(const EncodingTable& other)
{
    _head = nullptr;
    _tail = nullptr;
    std::shared_ptr<EncodingNode> curr_node = other._head;
    while (curr_node != nullptr)
    {
        push(curr_node->code.character, curr_node->code.encoding);
        curr_node = curr_node->next;
    }
}

EncodingTable& EncodingTable::operator=(const EncodingTable& other)
{
    _head = nullptr;
    _tail = nullptr;
    std::shared_ptr<EncodingNode> curr_node = other._head;
    while (curr_node != nullptr)
    {
        push(curr_node->code.character, curr_node->code.encoding);
        curr_node = curr_node->next;
    }
    return *this;
}

EncodingTable::~EncodingTable()
{
    _tail = nullptr;
    _head->~EncodingNode();
}

/// @brief add a new entry to EncodingTable with the provided character and 
/// corresponding huffman code
/// @param character a single character
/// @param encoding character's huffman code
void EncodingTable::push(std::string character, std::string encoding)
{
    Encoding code {character, encoding};
    std::shared_ptr<EncodingNode> node 
        = std::shared_ptr<EncodingNode>(new EncodingNode(code));

    if (_head == nullptr)
    {
        _head = node;
    }
    else
    {
        _tail->next = node;
    }
    _tail = node;
}

/// @brief Overloaded << to allow writing the contents of EncodingTable to 
/// a std::ostream. This overload writes each entry as:
///   character - encoding
/// for each character and encoding at each node
/// @param os an ostream
/// @param et an EncodingTable
/// @return an ostream with the character representation of et.
std::ostream& operator<<(std::ostream& os, EncodingTable& et)
{
    std::shared_ptr<EncodingTable::EncodingNode> curr_node = et._head;
    while(curr_node != nullptr)
    {
        os << curr_node->code.character << " - ";
        os << curr_node->code.encoding << std::endl;
        curr_node = curr_node->next;
    }

    return os;
}
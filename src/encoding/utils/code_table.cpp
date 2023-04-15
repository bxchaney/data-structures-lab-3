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

EncodingTable::~EncodingTable()
{
    _tail = nullptr;
    _head->~EncodingNode();
}

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
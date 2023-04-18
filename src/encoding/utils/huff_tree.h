/**
 * HuffTree is a huffman tree. It is constructed by a Huffman object and
 * has overloaded methods to facilitate determining which of two huffman
 * trees has greater or lesser precedence and to combine two huffman trees
 * into one. This ADT also allows the user to get the encoding for a given
 * charcter and returns the character for a given encoding.
 * 
 */

#pragma once 
#include<memory>
#include<string>
#include<iostream>

struct HuffNode
{
    std::string str;
    int total;
    bool is_leaf;

    std::shared_ptr<HuffNode> left;
    std::shared_ptr<HuffNode> right;

    HuffNode() = default;
    HuffNode(std::string&, int);

    friend std::ostream& operator<<(std::ostream&, const HuffNode&);
};

class HuffTree
{
    private:
        
        std::shared_ptr<HuffNode> root;

    public:

        HuffTree() = default;
        HuffTree(std::string, int);
        ~HuffTree() = default;

        HuffTree(const HuffTree&);
        HuffTree& operator = (const HuffTree&);
        HuffTree& operator=(const HuffTree&&);

        bool is_character_encoding(std::string&);
        std::string& get_character(std::string&);
        std::string get_code(std::string&);

        friend HuffTree operator + (HuffTree&, HuffTree&);
        friend bool operator < (HuffTree&, HuffTree&);
        friend std::ostream& operator<<(std::ostream&, const HuffTree&);
};
#pragma once 
#include<memory>
#include<string>
#include<iostream>


class HuffTree
{
    private:
        struct HuffNode
        {
            std::string str;
            int total;

            std::shared_ptr<HuffNode> left;
            std::shared_ptr<HuffNode> right;

            HuffNode() = default;
            HuffNode(std::string&, int);
        };

        std::shared_ptr<HuffNode> root;

    public:

        HuffTree() = default;
        HuffTree(std::string, int);
        ~HuffTree() = default;

        HuffTree(const HuffTree&);
        HuffTree& operator = (const HuffTree&);
        HuffTree& operator=(const HuffTree&&);

        friend HuffTree operator + (HuffTree&, HuffTree&);
        friend bool operator < (HuffTree&, HuffTree&);
        friend std::ostream& operator<<(std::ostream&, const HuffTree&);
};
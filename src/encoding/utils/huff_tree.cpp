#include<iostream>
#include<memory>
#include<string>
#include"huff_tree.h"

HuffTree::HuffNode::HuffNode(std::string& str, int tot)
{
    this->str = str;
    total = tot;
    is_leaf = true;
    left = nullptr;
    right = nullptr;
}

HuffTree::HuffTree(std::string str, int total)
{
    root = std::shared_ptr<HuffNode>(new HuffNode(str,total));
}

HuffTree::HuffTree(const HuffTree& other)
{
    root = other.root;
}

HuffTree& HuffTree::operator=(const HuffTree& other)
{
    root = other.root;
    return *this;
}

HuffTree& HuffTree::operator=(const HuffTree&& other)
{
    root = other.root;
    return *this;
}

HuffTree operator + (HuffTree& l_op, HuffTree& r_op)
{
    std::string new_str = l_op.root->str + r_op.root->str;
    int new_total = l_op.root->total + r_op.root->total;
    HuffTree new_huff;
    new_huff.root 
        = std::shared_ptr<HuffTree::HuffNode>(
            new HuffTree::HuffNode(new_str, new_total));
    new_huff.root->is_leaf = false;
    new_huff.root->left = l_op.root;
    new_huff.root->right = r_op.root;
    return new_huff;
}

bool operator < (HuffTree& l_op, HuffTree& r_op)
{
    if (l_op.root->total < r_op.root->total)
    {
        return true;
    }
    // same total tiebreak
    else if (l_op.root->total == r_op.root->total)
    {
        return l_op.root->str < r_op.root->str;
    }
    else 
    {
        return false;
    }
    
}

std::ostream& operator<< (std::ostream& os, const HuffTree& huff)
{
    os << huff.root->str << "," << huff.root->total << " ";
    if (huff.root->left != nullptr)
    {
        os << huff.root->left->str << "," << huff.root->left->total << " ";
    }
    if (huff.root->right != nullptr)
    {
        os << huff.root->right->str << "," << huff.root->right->total << " ";
    }
    return os;
}
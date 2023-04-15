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

bool HuffTree::is_character_encoding(std::string& str)
{
    // given a string of 0's and 1's, confirm if that string is an encoded
    // letter
    std::shared_ptr<HuffNode> curr_node = root;
    for (int i = 0; i < str.length(); i++) 
    {
        auto c = str[i];
        if (c == '0')
        {
            curr_node = curr_node->left;
        }
        else 
        {
            curr_node = curr_node->right;
        }

        if (curr_node == nullptr) return false;
    }
    return curr_node->is_leaf;
}

std::string HuffTree::get_character(std::string& str)
{
    std::shared_ptr<HuffNode> curr_node = root;
    for (int i = 0; i < str.length(); i++) 
    {
        auto c = str[i];
        if (c == '0')
        {
            curr_node = curr_node->left;
        }
        else 
        {
            curr_node = curr_node->right;
        }

        if (curr_node == nullptr) return "";
    }
    return curr_node->str;
}


std::string HuffTree::get_code(std::string& c)
{
    std::string out = "";
    std::shared_ptr<HuffNode> curr_node = root;
    while(curr_node != nullptr && !curr_node->is_leaf)
    {
        if (curr_node->left->str.find(c) != std::string::npos)
        {
            curr_node = curr_node->left;
            out = out + "0";
        }
        else 
        {
            curr_node = curr_node->right;
            out = out + "1";
        }
    }
    return out;
}

HuffTree operator + (HuffTree& l_op, HuffTree& r_op)
{
    std::string new_str = l_op.root->str + r_op.root->str;
    int new_total = l_op.root->total + r_op.root->total;
    HuffTree new_huff;
    new_huff.root 
        = std::shared_ptr<HuffTree::HuffNode>(
            new HuffTree::HuffNode(new_str, new_total)
        );
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
        // if exactly one is a leaf, that one has lower precendence
        if (
            
            // left operand is a leaf and right operand is not
            (l_op.root->is_leaf && !r_op.root->is_leaf)
            ||
            // right operand is a leaf and left is not
            (!l_op.root->is_leaf && r_op.root->is_leaf))
        {
            return l_op.root->is_leaf;
        }
        // if above case is false, then either neither node is a leaf
        // or both are leaves. In these cases, we resolve ties by 
        // alphabetical order.
        else 
        {
            return l_op.root->str < r_op.root->str;
        }        
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
#include<iostream>
#include<memory>
#include<string>
#include"huff_tree.h"

HuffNode::HuffNode(std::string& str, int tot)
{
    this->str = str;
    total = tot;
    is_leaf = true;
    left = nullptr;
    right = nullptr;
}

std::ostream& operator<<(std::ostream& os, const HuffNode& node)
{
    os << node.str << ": " << node.total << "; " << std::endl;
    if (node.left != nullptr)
    {
        os << *node.left;
    }
    if (node.right != nullptr)
    {
        os << *node.right;
    }
    return os;
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

/// @brief returns true if str represents a valid path through the tree
/// to a leaf containing a character
/// @param str a string of 0's and 1's representing an encoding
/// @return 
bool HuffTree::is_character_encoding(std::string& str)
{
    // given a string of 0's and 1's, confirm if that string is an encoded
    // letter
    std::shared_ptr<HuffNode> curr_node = root;
    int str_size = str.length();
    for (int i = 0; i < str_size; i++) 
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

/// @brief returns the character that corresponds to the provided huffman
/// code
/// @param str a string of 0's and 1's representing a path through the
/// tree
/// @return 
std::string& HuffTree::get_character(std::string& str)
{
    std::shared_ptr<HuffNode> curr_node = root;
    int str_size = str.length();
    for (int i = 0; i < str_size; i++) 
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
    }
    return curr_node->str;
}

/// @brief returns the encoding, as a string of 0's and 1's, for a given
/// character
/// @param c the character to be searched for
/// @return 
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
        else if (curr_node->right->str.find(c) != std::string::npos)
        {
            curr_node = curr_node->right;
            out = out + "1";
        }
        else
        {
            break;
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
        = std::shared_ptr<HuffNode>(
            new HuffNode(new_str, new_total)
        );
    new_huff.root->is_leaf = false;
    new_huff.root->left = l_op.root;
    new_huff.root->right = r_op.root;
    return new_huff;
}

/// @brief overload to facilitate precedence comparisions between two huffman
/// trees
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
    os << *huff.root;
    return os;
}
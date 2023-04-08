#include<iostream>
#include<memory>
#include<string>
#include"tree_map.h"

TreeRecord::TreeRecord()
{
    str = "";
    frequency = 0;
}

TreeRecord::TreeRecord(std::string str)
{
    this->str = str;
    frequency = 1;
}

TreeMap::TreeNode::TreeNode()
{
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
    balance = 0;
    TreeRecord record {};
}

TreeMap::TreeNode::TreeNode(TreeRecord& rec)
{
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
    balance = 0;
    record = std::move(rec);
}

TreeMap::TreeNode::TreeNode(const TreeNode& other)
{
    parent = other.parent;
    left = other.left;
    right = other.right;
    record = std::move(other.record);
}

TreeMap::TreeMap()
{
    root = nullptr;
    _size = 0;
    
}

TreeMap::TreeMap(const TreeMap& other)
{
    root = nullptr;
    _size = 0;

}

TreeMap::~TreeMap()
{
    if (root != nullptr)
    {
        root->~TreeNode();
    }
}

void TreeMap::insert(std::string str)
{
    _size++;
    TreeRecord rec {str};
    if (root == nullptr)
    {
        root = std::shared_ptr<TreeNode>(new TreeNode(rec));
        return;
    }


    std::shared_ptr<TreeNode> node = std::shared_ptr<TreeNode>(
            new TreeNode(rec)
        );

    std::shared_ptr<TreeNode> curr = root;
    while (curr != nullptr)
    {
        if (str < curr->record.str)
        {
            if (curr->left == nullptr)
            {
                set_child(curr, 0, node);
            }
            else 
            {
                curr = curr->left;
            }
        }
        else
        {
            if (curr->right == nullptr)
            {
                // set right as new node
                set_child(curr, 1, node);
            }
            else 
            {
                curr = curr->right;
            }
        }
    }

    node = node->parent;
    while (node != nullptr)
    {
        rebalance(node);
        node = node->parent;
    }
}

bool TreeMap::search(std::string str)
{
    if (root == nullptr) // tree is empty
    {
        return false;
    }

    std::shared_ptr<TreeNode> curr = root;
    while (curr != nullptr)
    {
        if (curr->record.str == str)
        {
            return true;
        }
        else if (str < curr->record.str)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return false;
}

void TreeMap::update_height(std::shared_ptr<TreeNode> node)
{
    int left_height = -1;
    if (node->left != nullptr)
    {
        left_height = node->left->height;
    }
    
    int right_height = -1;
    if (node->right != nullptr)
    {
        right_height = node->right->height;
    }
    
    node->height = max(left_height, right_height) + 1;
}

void TreeMap::set_child(
    std::shared_ptr<TreeNode> parent,
    int which_child,
    std::shared_ptr<TreeNode> new_child
)
{
    if (which_child == 0) // left child
    {
        parent->left = new_child;
    }
    else
    {
        parent->right = new_child;
    }
    if (new_child != nullptr)
    {
        new_child->parent = parent;
    }

    update_height(parent);
}

void TreeMap::replace_child(
    std::shared_ptr<TreeNode> parent,
    std::shared_ptr<TreeNode> curr_node,
    std::shared_ptr<TreeNode> new_node
)
{
    if (parent->left == curr_node)
    {
        set_child(parent, 0, new_node);
    }
    else if (parent->right == curr_node)
    {
        set_child(parent, 1, new_node);
    }
    else
    {
        std::cout << "Failed to replace with node: ";
        std::cout << new_node->record.str << " ";
        std::cout << new_node->record.frequency << std::endl;
    }
}

int TreeMap::get_balance(std::shared_ptr<TreeNode> node)
{
    int left_height = -1;
    if (node->left != nullptr)
    {
        left_height = node->left->height;
    }
    
    int right_height = -1;
    if (node->right != nullptr)
    {
        right_height = node->right->height;
    }

    return left_height - right_height;
}

void TreeMap::rotate_right(std::shared_ptr<TreeNode> node)
{
    // assume that the left child is non-null
    std::shared_ptr<TreeNode> left_right_child = node->left->right;
    if (node->parent != nullptr)
    {
        replace_child(node->parent, node, node->left);    
    }
    else 
    {
        root = node->left;
        root->parent = nullptr;
    }

    set_child(node->left, 1, node);
    set_child(node, 0, left_right_child);
}

void TreeMap::rotate_left(std::shared_ptr<TreeNode> node)
{
    // assume that the right child is non-null
    std::shared_ptr<TreeNode> right_left_child = node->right->left;
    if (node->parent != nullptr)
    {
        replace_child(node->parent, node, node->right);    
    }
    else 
    {
        root = node->right;
        root->parent = nullptr;
    }

    set_child(node->right, 0, node);
    set_child(node, 1, right_left_child);
}

void TreeMap::rebalance(std::shared_ptr<TreeNode> node)
{
    update_height(node);
    int node_balance = get_balance(node);
    if (node_balance == -2)
    {
        if (get_balance(node->right) == 1)
        {
            rotate_right(node->right);
        }
        rotate_left(node);
    }
    else if (node_balance == 2)
    {
        if (get_balance(node->left) == -1)
        {
            rotate_left(node->left);
        }
        rotate_right(node);
    }
}

TreeRecord& TreeMap::get(std::string str)
{
    // assuming that the tree is non-empty and str is a member of the tree
    std::shared_ptr<TreeNode> curr = root;
    while (curr != nullptr)
    {
        if (curr->record.str == str)
        {
            break; 
        }
        else if (str < curr->record.str)
        {
            curr = curr->left;
        }
        else 
        {
            curr = curr->right;
        }
    }
    return curr->record;
}

TreeRecord& TreeMap::operator[](std::string str)
{
    if (!search(str))
    {
        insert(str);
    }

    return get(str);
}

int TreeMap::max(int a, int b)
{
    if (a >= b) return a;
    return b;
}
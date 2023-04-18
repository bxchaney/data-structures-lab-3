#include<iostream>
#include<memory>
#include<string>
#include"tree_map.h"
#include"freq_table.h"

TreeRecord::TreeRecord()
{
    str = "";
    frequency = 0;
}

TreeRecord::TreeRecord(std::string str)
{
    this->str = str;
    frequency = 0;
}

TreeMap::TreeNode::TreeNode()
{
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
    TreeRecord record {};
}

TreeMap::TreeNode::TreeNode(TreeRecord& rec)
{
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
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

TreeMap::~TreeMap()
{
    if (root != nullptr)
    {
        root->~TreeNode();
    }
}

/// @brief adds a new node to the tree with the provided string value
/// @param str a single character string
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
    // searching for a place to insert the new node
    while (curr != nullptr)
    {
        if (str < curr->record.str)
        {
            if (curr->left == nullptr)
            {
                set_child(curr, 0, node);
                break;
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
                break;
            }
            else 
            {
                curr = curr->right;
            }
        }
    }
    // rebalance the tree if necessary
    node = node->parent;
    while (node != nullptr)
    {
        rebalance(node);
        node = node->parent;
    }
}

/// @brief searches for a given string in the tree. Returns true if that
/// string is already in the tree
/// @param str a single character string
/// @return 
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

/// @brief updates the height of a node by taking the max height of its
/// children and adding 1
/// @param node 
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

/// @brief sets a new child as either the left or right child of the parent.
/// This method also updates the height of the parent after adding the new 
/// child.
/// @param parent a node recieving a new child
/// @param which_child 0 for left child or 1 for right child
/// @param new_child 
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

/// @brief this method replaces a node's child with another node
/// @param parent node with a child being replaced
/// @param curr_node current child
/// @param new_node new child
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
        // should never be accessed
        std::cout << "Failed to replace with node: ";
        std::cout << new_node->record.str << " ";
        std::cout << new_node->record.frequency << std::endl;
    }
}

/// @brief returns the balance of a node, taken as the height of the 
/// left child less the height of the right child. If either child is
/// null, it's height is -1
/// @param node 
/// @return 
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

/// @brief performs a right rotation at node
/// @param node the node being rotated about
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

/// @brief performs a left rotation at node
/// @param node the node being rotated about
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

/// @brief this method is called after a new node is added and the tree
/// is now out of balance. It performs rotations at the unbalanced nodes.
/// @param node the node being rebalanced.
void TreeMap::rebalance(std::shared_ptr<TreeNode> node)
{
    update_height(node);
    int node_balance = get_balance(node);
    if (node_balance == -2)
    {
        // right-left rotation case
        if (get_balance(node->right) == 1)
        {
            rotate_right(node->right);
        }
        rotate_left(node);
    }
    else if (node_balance == 2)
    {
        // left-rigth rotation case
        if (get_balance(node->left) == -1)
        {
            rotate_left(node->left);
        }
        rotate_right(node);
    }
}

/// @brief returns the TreeRecord that has str as one of its fields
/// @param str a single character string
/// @return 
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
    // curr should never be nullptr, by construction
    // so this should never result in a segfault
    return curr->record;
}

/// @brief allowing the user to access elements of TreeMap with []
/// @param str
/// @return 
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
    return (a >= b) ? a : b;
}

/// @brief this method populates ft with the str and frequency values stored
/// at every node.
/// @param ft an empty FrequencyTable
/// @param node the root node
void TreeMap::push_values(FrequencyTable& ft, std::shared_ptr<TreeNode> node)
{
    if (node == nullptr) return;
    push_values(ft, node->left);
    ft.push(node->record.str, node->record.frequency);
    push_values(ft, node->right);
}

/// @brief This method populates ft with the str and frequency values stored
/// at every node of the tree.
/// @param ft an empty FrequencyTable
void TreeMap::fill_freq_table(FrequencyTable& ft)
{
    // Assuming the ft is empty, push all elements in TreeMap
    // to ft in order.
    push_values(ft, root);
}
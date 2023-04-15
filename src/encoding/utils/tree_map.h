#pragma once
#include<memory>
#include<string>
#include"freq_table.h"

struct TreeRecord
{
    std::string str;
    int frequency;

    TreeRecord();
    TreeRecord(std::string);

    ~TreeRecord() = default;

    TreeRecord& operator++(int)
    {
        frequency++;
        return *this;
    }
};

class TreeMap
{
    private:
        struct TreeNode
        {
            std::shared_ptr<TreeNode> parent, left, right;
            int height;
            
            TreeRecord record;
            

            TreeNode();
            TreeNode(TreeRecord&);

            ~TreeNode() = default;
            TreeNode(const TreeNode&);
        };
        
        std::shared_ptr<TreeNode> root;
        int _size;

        void insert(std::string);
        TreeRecord& get(std::string);

        void update_height(std::shared_ptr<TreeNode>);
        void set_child(
            std::shared_ptr<TreeNode>,
            int,
            std::shared_ptr<TreeNode>
        );
        void replace_child(
            std::shared_ptr<TreeNode>,
            std::shared_ptr<TreeNode>,
            std::shared_ptr<TreeNode>
        );

        int get_balance(std::shared_ptr<TreeNode>);

        void rotate_right(std::shared_ptr<TreeNode>);
        void rotate_left(std::shared_ptr<TreeNode>);

        void rebalance(std::shared_ptr<TreeNode>);

        int max(int, int);

        void visit(std::shared_ptr<TreeNode>);

        void push_values(FrequencyTable&, std::shared_ptr<TreeNode>);

    public:

        TreeMap();
        ~TreeMap();

        TreeMap(const TreeMap&) = delete;

        bool search(std::string);

        // allowing user to access nodes in this object via bracket op
        TreeRecord& operator[] (std::string);

        void preorder_traversal();

        void fill_freq_table(FrequencyTable&);

};
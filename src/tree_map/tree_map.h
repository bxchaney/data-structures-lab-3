#include<memory>
#include<string>


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
            int balance;
            
            TreeRecord record;
            

            TreeNode();
            TreeNode(TreeRecord&);

            ~TreeNode() = default;
            TreeNode(const TreeNode&);
            // TreeNode& operator=(const TreeNode&);
            // TreeNode& operator=(const TreeNode&&);
        };
        
        std::shared_ptr<TreeNode> root;
        int _size;

        void insert(std::string);
        bool search(std::string);
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


    public:

        TreeMap();
        ~TreeMap();

        TreeMap(const TreeMap&);

        TreeMap& operator=(const TreeMap&);

        // allowing user to access nodes in this object via bracket op
        TreeRecord& operator[] (std::string);

        
        // void remove(std::string);

};
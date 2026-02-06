/*
* Exercise 13.28: 
* Given the following classes, implement a default constructor
* and the necessary copy-control members.
*/

#include <string>

class TreeNode {
public: 
    // 构造函数：移除冲突，只保留一个带默认参数的构造函数
    TreeNode(const std::string &val = std::string(), 
             TreeNode *l = nullptr, TreeNode *r = nullptr)
        : value(val), count(1), left(l), right(r) { }
    
    // 正确的拷贝构造函数（递归深拷贝）
    TreeNode(const TreeNode &rhs)
        : value(rhs.value), count(rhs.count),
          left(nullptr), right(nullptr) {
        // 递归深拷贝左右子树
        if (rhs.left) left = new TreeNode(*rhs.left);
        if (rhs.right) right = new TreeNode(*rhs.right);
    }
    
    // 拷贝赋值运算符（传统方法，不使用swap）
    TreeNode& operator=(const TreeNode &rhs) {
        // 1. 检查自赋值
        if (this == &rhs) return *this;
        
        // 2. 创建临时子树（异常安全的关键）
        TreeNode *newLeft = nullptr;
        TreeNode *newRight = nullptr;
        
        try {
            if (rhs.left) newLeft = new TreeNode(*rhs.left);
            if (rhs.right) newRight = new TreeNode(*rhs.right);
        } catch (...) {
            delete newLeft;
            delete newRight;
            throw;  // 重新抛出异常
        }
        
        // 3. 释放旧资源
        delete left;
        delete right;
        
        // 4. 赋值新资源
        value = rhs.value;
        count = rhs.count;
        left = newLeft;
        right = newRight;
        
        return *this;
    }
    
    // 析构函数
    ~TreeNode() {
        delete left;
        delete right;
    }
    
private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;
};


class BinStrTree {
public:
    // 默认构造函数
    BinStrTree() : root(new TreeNode()), use(new std::size_t(1)) { }
    
    // 构造函数（接受 TreeNode 参数）
    BinStrTree(const TreeNode &node) 
        : root(new TreeNode(node)), use(new std::size_t(1)) { }
    
    // 拷贝构造函数（共享资源）
    BinStrTree(const BinStrTree &rhs) 
        : root(rhs.root), use(rhs.use) {
        ++*use;
    }
    
    // 拷贝赋值运算符（传统方法）
    BinStrTree& operator=(const BinStrTree &rhs) {
        // 1. 检查自赋值
        if (this == &rhs) return *this;
        
        // 2. 增加右操作数引用计数（防止自赋值问题）
        ++*rhs.use;
        
        // 3. 减少左操作数引用计数，如果为0则释放
        if (--*use == 0) {
            delete root;
            delete use;
        }
        
        // 4. 共享资源
        root = rhs.root;
        use = rhs.use;
        
        return *this;
    }
    
    // 析构函数
    ~BinStrTree() {
        if (--*use == 0) {
            delete root;
            delete use;
        }
    }
    
private:
    TreeNode *root;
    std::size_t *use;  // 引用计数器
};
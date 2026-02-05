/*
* Exercise 13.22: Assume that we want HasPtr to behave like a value. That
* is, each object should have its own copy of the string to which the objects
* point. We’ll show the definitions of the copy-control members in the next
* section. However, you already know everything you need to know to
* implement these members. Write the HasPtr copy constructor and copy-
* assignment operator before reading on.
*/

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) { }

    //add copy constructor declaration
    HasPtr(const HasPtr&);

    //add copy-assignment operator 
    HasPtr& operator= (const HasPtr& temp); 

    //destructor, 默认合成的已经满足不了了这次
    //由于类中的指针成员相对于其他对象都是独立的
    //因此每个成员也需要销毁自己的指针成员，在销毁的时候
    ~HasPtr(){
        if (this->ps) delete this->ps; //销毁并释放内存
        this->ps = nullptr; 
    }; 

private:
    std::string *ps;
    int i;
};

//definition of copy constructor
HasPtr::HasPtr(const HasPtr& arg): 
i(arg.i), ps(new std::string(*arg.ps)){}

//definition of copy-assignment operator
//这样的深度拷贝才能使副本和原始对象是互相独立的
//互相独立的才能是valuelike 
HasPtr& HasPtr::operator= (const HasPtr& rhs){

    //自赋值检查
    if (this == &rhs) return *this; 

    // 2. 创建临时副本（异常安全）
    std::string *new_ps = new std::string(*rhs.ps);
    int new_i = rhs.i;
    
    // 3. 释放旧资源
    if (ps) delete ps;
    
    // 4. 分配新资源
    ps = new_ps;
    i = new_i;
    
    // 5. 返回当前对象的引用
    return *this;
}




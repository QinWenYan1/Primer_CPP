/*
* Exercise 13.22: Assume that we want HasPtr to behave like a value. That
* is, each object should have its own copy of the string to which the objects
* point. We’ll show the definitions of the copy-control members in the next
* section. However, you already know everything you need to know to
* implement these members. Write the HasPtr copy constructor and copy-
* assignment operator before reading on.
*/

#ifndef HASPTR_H
#define HASPTR_H

#include <string>
#include <iostream>

class HasPtr {
    //swap函数
    friend void swap(HasPtr&, HasPtr&); 
    std::string *ps;
    int i;

public:
    HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) { }

    //add copy constructor definition 
    HasPtr(const HasPtr& arg): i(arg.i), ps(new std::string(*arg.ps)){};

    //add copy-assignment operator 
    HasPtr& operator= (HasPtr); 

    //add < operator definition
    bool operator< (const HasPtr &rhs) const { return *(this->ps) < *(rhs.ps); }; 

    //destructor, 默认合成的已经满足不了了这次
    //由于类中的指针成员相对于其他对象都是独立的
    //因此每个成员也需要销毁自己的指针成员，在销毁的时候
    ~HasPtr(){
        if (this->ps) delete this->ps; //销毁并释放内存
        this->ps = nullptr; 
    }; 

    const std::string &getString() const { return *(this->ps); }

};
//面向HasPr的swap函数的实现
inline void swap(HasPtr &arg1, HasPtr &arg2){
    using std::swap; //防止污染外面的命名空间
    std::cout << "swap(HasPtr&, HasPtr&) executing" << std::endl;
    swap(arg1.i, arg2.i); 
    swap(arg1.ps, arg2.ps); 
}

//definition of copy-assignment operator
//这样的深度拷贝才能使副本和原始对象是互相独立的
//互相独立的才能是valuelike 
HasPtr& HasPtr::operator= (HasPtr rhs){
    //重构HasPtr, 使用swap来实现
    swap(*this, rhs); 
    return *this; 
}

#endif 
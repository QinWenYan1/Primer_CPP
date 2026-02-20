/*
* Exercise 13.27: 
* Define your own reference-counted version of HasPtr.
*/

#ifndef HASPTR_H
#define HASPTR_H

#include <string>
#include <iostream>

/*
* Exercise 13.54: 
* What would happen if we defined a HasPtr move-
* assignment operator but did not change the copy-and-swap operator? Write
* code to test your answer.
*/

#include <string>

class HasPtr {
public:

    const std::string &getString() const { return *ps; }

    friend void swap(HasPtr&, HasPtr&); 
    HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0) { }

    //definition of copy constructor
    HasPtr(const HasPtr& arg): i(arg.i), ps(new std::string(*arg.ps)){}

    //add copy-assignment operator 
    HasPtr& operator= (const HasPtr &rhs){
        std::cout << "executing copy-swap assignment "<< std::endl; 
        auto temp = rhs; 
        swap(*this, temp); 
        return *this; 
    }; 

    //add definition move assignment operator 
    HasPtr &operator=(HasPtr &&rhs) noexcept {
        std::cout << "executing move assignment "<< std::endl; 
        //自检查
        if (this != &rhs ){ //不是一样才开始
            delete ps; 
            ps = rhs.ps; 
            rhs.ps = nullptr; //置零，防止意外访问
            i = rhs.i; 
        }
        return *this; 
    }

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

inline void swap(HasPtr &lhs, HasPtr &rhs){
    using std::swap; 
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i); 
}

#endif 
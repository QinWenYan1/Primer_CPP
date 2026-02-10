/*
* Exercise 13.27: 
* Define your own reference-counted version of HasPtr.
*/

#ifndef HASPTR_H
#define HASPTR_H

#include <string>

class HasPtr {

public:
    HasPtr(const std::string &s = std::string()):
    ps(new std::string(s)), i(0), useCountPtr(new unsigned(1)) { }

    //add pointerlike copy constructor definition
    HasPtr(const HasPtr& arg): 
        i(arg.i), ps(arg.ps), useCountPtr(arg.useCountPtr){ ++*useCountPtr; }

    //add pointerlike copy-assignment operator 
    HasPtr& operator= (const HasPtr& rhs){
        //先自加引用计数防止自赋值的时候误删除
        ++*rhs.useCountPtr; 
        if (--*useCountPtr == 0) {
            delete ps; 
            delete useCountPtr; 
        }

        i = rhs.i;
        ps = rhs.ps;
        useCountPtr = rhs.useCountPtr;

        return *this; 

    }; 

    ~HasPtr(){
        //先减引用计数
        if(--*useCountPtr == 0){
            delete ps; 
            delete useCountPtr; 
        }

    }; 

private:
    std::string *ps;
    int i;
    unsigned *useCountPtr; //引用计数指针
};

#endif 

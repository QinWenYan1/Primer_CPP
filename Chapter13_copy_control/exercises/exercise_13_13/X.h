/*
* Exercise 13.13: 
* A good way to understand copy-control members and
* constructors is to define a simple class with these members in which each
* member prints its name, 
*/

#ifndef X_H
#define X_H
#include <iostream>

struct X {

    //default constructor
    X() = default; 

    // constructor
    X(int temp) {
        std::cout << "initialising with value " << temp << std::endl;
        this->core = temp; 
    }

    //copy initialization 
    X(const X& temp) {
        std::cout << "X(const X&)" << std::endl;
        this->core = temp.core; 
    }

    //assignemnt-copy operator 
    X &operator=(const X& temp){ 
        this->core = temp.core; 
        return *this; 
    }
    
    //destructor 
    ~X(){}

    //getter 
    const unsigned &getValue() const {
        return this->core; 
    }

private:
    unsigned core = 1; 
};

#endif

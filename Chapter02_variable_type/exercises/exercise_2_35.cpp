#include <iostream>
#include <typeinfo>

/*
* Exercise 2.35: 
* Determine the types deduced in each of the following
* definitions. Once you’ve figured out the types, write a program to see
* whether you were correct.
*/

int main(void){

    const int i = 42;
    auto j = i; // j is int 
    const auto &k = i; // k is const int&
    auto &r = i; // r is const int& 
    auto *p = &i; // p is const int*
    const auto j2 = i, &k2 = i; // j2 is const int, k2 is const int&
    // j2 = 3; error 
    

    std::cout << "Type of j: " << typeid(j).name() << std::endl;
    std::cout << "Type of k: " << typeid(k).name() << std::endl;
    std::cout << "Type of r: " << typeid(r).name() << std::endl;
    std::cout << "Type of p: " << typeid(p).name() << std::endl;
    std::cout << "Type of j2: " << typeid(j2).name() << std::endl;
    std::cout << "Type of k2: " << typeid(k2).name() << std::endl;

}

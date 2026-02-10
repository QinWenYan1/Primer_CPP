/*
* Exercise 13.30: 
* Write and test a swap function for your valuelike version of
* HasPtr. Give your swap a print statement that notes when it is executed.
*/

#include <iostream>
#include "HasPtr.h"

using namespace std;

int main(){

    HasPtr hp("Hello this is HasPtr"); 
    HasPtr anotherHp("Hello this is another HasPtr"); 
    HasPtr emptyHp; 

    //test HasPtr的swap函数
    emptyHp = hp; 
    std::cout << emptyHp.getString() << std::endl; 

    swap(hp, anotherHp); 
    std::cout << hp.getString() << std::endl;
    std::cout << anotherHp.getString() << std::endl;


}
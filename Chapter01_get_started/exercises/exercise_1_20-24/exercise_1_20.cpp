#include <iostream>
#include "Sales_item.h"

/*
* Exercise 1.20:
* Use it to write a program that reads a set of book sales
* transactions, writing each transaction to the standard output.
*/

/*
* Exercise 1.21:
* Write a program that reads two Sales_item objects that
* have the same ISBN and produces their sum.
*/

int main(void){

    //create two book objects
    Sales_item item1, item2; 

    //print their transaction line by line
    std::cin >> item1 >> item2; 
    std::cout << item1 << std::endl; 
    std::cout << item2 << std::endl; 

    //print sum of two transactions of books 
    std::cout << item1 + item2 << std::endl;

    return 0; 

}
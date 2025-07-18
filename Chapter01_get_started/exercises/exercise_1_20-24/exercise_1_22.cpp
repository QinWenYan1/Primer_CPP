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

    Sales_item item, total_item; 
    while( std::cin >> item ){

        total_item += item; 

    } 

    std::cout << "The total transactions is: \n" << total_item << std::endl; 

}
#include <iostream>
#include "Sales_item.h"

/*
* Exercise 1.23:
* Write a program that reads several transactions and counts
* how many transactions occur for each ISBN.
*/

/*
* Exercise 1.24:
* Test the previous program by giving multiple transactions
* representing multiple ISBNs. The records for each ISBN should be grouped
* together.
*/

int main(void){

    Sales_item item1, item2;
    // this is to count how many times this book appear
    int count; 

    // check this must have input here
    if( std::cin >> item1 ){

        while( std::cin >> item2 ){
            
            // the isbn is identical 
            if( item1.isbn == item2.isbn ){

                item1 = item1 + item2; 

            }else{

                // the isbn is not identical
                std::cout << item1 << std::endl; 
                item1 = item2;  

            }

        }

        //print out the all transaction in the buffer
        std::cout << item1 << std::endl; 

    }

}
#include <iostream>

/*
* Exercise 1.11:
* Write a program that prompts the user for two integers.
* Print each number in the range specified by those two integers.
*/


int main(void){

    // the p is the number we will print 
    int v = 0, i = 0; 

    std::cout << " input two integers below: \n" << std::endl; 
    std::cin >> v >> i;

    if( v < i ){

        //we'll start from the smaller number 
        v++;  
        
        std::cout << "outcome is here: \n";

        while( v < i){
            
            std::cout << v << " " << std::endl;
            v++;

        }
    }


}
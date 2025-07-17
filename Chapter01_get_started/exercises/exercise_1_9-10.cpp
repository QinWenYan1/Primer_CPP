#include <iostream>

/*
* Exercise 1.9:
* Write a program that uses a while to sum the numbers from
* 50 to 100.
*/

/*
* Exercise 1.10: 
* In addition to the ++ operator that adds 1 to its operand,
* there is a decrement operator (--) that subtracts 1. Use the decrement
* operator to write a while that prints the numbers from ten down to zero.
*/

int main(void){

    int val = 100, sum = 0; 

    while( val >= 50 ){

        sum += val;
        val -- ; 

    }
    std::cout << "The sum from 50 to 100 is: "
    << sum << " \n " << std::endl; 

}
#include <iostream>

/*
* Exercise 1.16:
* Write your own version of a program that prints the sum of
* a set of integers read from cin.
*/

int main(void){

    int sum = 0, num = 0;

    while( ( std::cin >> num ) ){

        sum += num; 

    }

    std::cout << "The sum of the input numbers is: " << sum << std::endl; 

}
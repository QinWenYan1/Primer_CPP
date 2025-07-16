#include <iostream>

/*
* Exercise 1.4:
* Our program used the addition operator, +, to add two
* numbers. Write a program that uses the multiplication operator, *, to print
* the product instead.
*/

/*
* Exercise 1.5: 
* We wrote the output in one large statement. Rewrite the
* program to use a separate statement to print each operand.
*/

int main(void){

    /* giving it default value*/
    int num1 = 0;
    int num2 = 0;

    std::cout << "please input two number here:";
    std::cout << std::endl;
    std::cin >> num1;
    std::cin >> num2; 
    std::cout << "the product of ";
    std::cout << num1;
    std::cout << " with " << num2; 
    std::cout << " is "; 
    std::cout << num1 * num2; 
    std::cout << std::endl; 

}
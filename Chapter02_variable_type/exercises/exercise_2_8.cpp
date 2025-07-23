#include <iostream>

/*
* Exercise 2.8:
* Using escape sequences, write a program to print 2M followed
* by a newline. Modify the program to print 2, then a tab, then an M, followed
* by a newline.
*/

int main(void){

    std::cout << "2" "\t" "M" "\n" << std::endl; 

    return 0;

}
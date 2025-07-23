#include <iostream>

/*
* Exercise 2.3:
* What output will the following code produce?
*/

/*
* Exercise 2.4:
* Write a program to check whether your predictions were
* correct. If not, study this section until you understand 
* what the problem is.
*/

int main(void){

    unsigned u = 10, u2 = 42;
    std::cout << u2 - u << std::endl; //32
    std::cout << u - u2 << std::endl; //一个非常大的数
    int i = 10, i2 = 42; 
    std::cout << i2 - i << std::endl; //32
    std::cout << i - i2 << std::endl; //-32

    std::cout << i - u << std::endl;  //0
    std::cout << u - i << std::endl;  //0

}
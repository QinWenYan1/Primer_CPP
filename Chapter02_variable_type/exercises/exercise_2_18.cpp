#include <iostream>

/*
* Exercise 2.18: 
* Write code to change the value of a pointer. Write code to
* change the value to which the pointer points.
*/

int main(void){

    double i = 0, *ip = &i;
    double j = 1, *jp = &j;

    std::cout << "The original value of i is: " << *ip << std::endl;
    std::cout << "The original value of j is: " << *jp << std::endl;

    //we change the value of object which the pointer addresses
    *ip = 3.14;
    *jp = 5.16; 

    std::cout << "changing the value of i and j" << std::endl; 
    std::cout << "The changed value of i is: " << *ip << std::endl;
    std::cout << "The changed value of j is: " << *jp << std::endl;

    //we swap the value of pointers themselves
    double *middle = nullptr;
    middle = ip;
    ip = jp, jp = middle; 

    std::cout << "swapping the value of ip and jp" << std::endl; 
    std::cout << "The changed value of i is: " << *ip << std::endl;
    std::cout << "The changed value of j is: " << *jp << std::endl;

}
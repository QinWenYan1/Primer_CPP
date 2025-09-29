#include <iostream>
#include "Chapter6.h"

using std::cout; 
using std::cin;
using std::endl; 

/*
* Exercise 6.9: 
* Write your own versions of the fact.cc and factMain.cc
* files. These files should include your Chapter6.h from the exercises in the
* previous section. Use these files to understand how your compiler supports
* separate compilation.
*/

int main(void){

    int input;

    cout << "Please input your number," 
         << "I'll calculate the factorial of the number for you ..."
         << endl; 
    
    cin >> input; 

    cout << "The factorial of " << input 
         << " is " << fact(input) << endl; 
    
}
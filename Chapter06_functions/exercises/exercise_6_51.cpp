#include <iostream>
#include <cstdlib>

using std::cout; 
using std::cin; 
using std::endl; 

/*
* Exercise 6.51: 
* Write all four versions of f. Each function should print a
* distinguishing message. Check your answers for the previous exercise. If your
* answers were incorrect, study this section until you understand why your
* answers were wrong.
*/

/*
* Answer: 
* a. ambiguous 
* b. f(int)
* c. f(int int)
* d. f(double, double=3.14)
*/

void f(){ cout << "Executing f() function ..." << endl; }

void f(int){ cout << "Executing f(int) function ..." << endl; }

void f(int, int){ cout << "Executing f(int int) function ..." << endl; }

void f(double, double = 3.14){ cout << "Executing f(double, double = 3.14) function ..."<< endl; }

int main(){
    //exercise_6_51.cpp:26:5: error: call to 'f' is ambiguous
    //26 |     f(2.56, 42);
    //   |     ^
    //f(2.56, 42);
    f(42);
    f(42, 0); 
    f(2.56, 3.14); 
    return EXIT_SUCCESS; 

}


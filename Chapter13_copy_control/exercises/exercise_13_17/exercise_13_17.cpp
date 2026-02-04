/*
* Exercise 13.17: 
* Write versions of numbered and f corresponding to the
* previous three exercises and check whether you correctly predicted the
* output.
*/
#include <iostream>
#include "Numbered.h"

void f ( Numbered s) { std::cout << s.mysn << std::endl; }

int main(){

    Numbered a, b = a, c = b; 
    f(a); 
    f(b); 
    f(c); 

}
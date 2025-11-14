#include <iostream>
#include "Sales_data.h"

using std::endl; 
using std::cout; 

/*
* Exercise 7.41: 
* Rewrite your own version of the Sales_data class to use
* delegating constructors. Add a statement to the body of each of the
* constructors that prints a message whenever it is executed. Write
* declarations to construct a Sales_data object in every way possible. Study
* the output until you are certain you understand the order of execution among
* delegating constructors.
*/


int main(){

    Sales_data data1("114514");
    Sales_data data2("1919", 110, 12); 

}
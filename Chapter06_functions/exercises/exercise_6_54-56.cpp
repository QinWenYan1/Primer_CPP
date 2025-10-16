#include <iostream>
#include <cstdlib>
#include <vector>

using std::cout;
using std::cin; 
using std::endl; 
using std::vector; 

/* 
* Exercise 6.54: 
* Write a declaration for a function that takes two int
* parameters and returns an int, and declare a vector whose elements have
* this function pointer type.
* 
* Exercise 6.55: Write four functions that add, subtract, multiply, and divide
* two int values. Store pointers to these values in your vector from the
* previous exercise.
* 
* Exercise 6.56: Call each element in the vector and print their result.
*/

int func(int, int); 
int add(int v1, int v2) { return (v1+v2); }
int sub(int v1, int v2) { return (v1 - v2); }
int mul(int v1, int v2){ return (v1 * v2); }
int divide(int v1, int v2) { return (v1/v2); }

int main(){


    vector<decltype(func)*> vfp = {add, mul, divide, sub};
    int v1 = 10, v2 = 110; 

    cout << "Testing outcome ..." << endl; 
    for ( auto op: vfp ){

        cout << op(v1, v2) << endl; 

    }

    return EXIT_SUCCESS;

}
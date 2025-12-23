#include <iostream>
#include <numeric>
#include <list>

using namespace std; 

/*
* Exercise 10.14: 
* Write a lambda that takes two ints and returns their sum.
*/

/*
* Exercise 10.15: 
* Write a lambda that captures an int from its enclosing
* function and takes an int parameter. 
* The lambda should return the sum of
* the captured int and the int parameter.
*/


int main(){

    // exercise 10.14 

    int i1 = 110; 
    int i2 = 120; 

    auto f =  [](int i1, int i2) -> int {return i1+i2;}; 
    cout << f(i1, i2) << endl; 

    //exercise 10.15
    auto f1 = [i1](int i2) { return i1 + i2; }; 
    cout << f1(i2) << endl; 


    //exercise 10.15
    list<int> listI = {132,134,3531,4353,253, 231};
    int sum = 0; 
    for_each(
        listI.begin(), 
        listI.end(), 
        [&sum](const int &num){ sum += num; }
    ); 

    cout << sum << endl; 
}
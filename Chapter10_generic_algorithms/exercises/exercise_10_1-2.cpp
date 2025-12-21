#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std; 

/*
* Exercise 10.1: 
* The algorithm header defines a function named count
* that, like find, takes a pair of iterators and a value. 
* count returns a count
* of how often that value appears. Read a sequence of ints into a vector
* and print the count of how many elements have a given value.
* 
* Exercise 10.2: Repeat the previous program, but read values into a list of
* strings.
*/

int main(){

    vector<int> vec = {1,2,3,4,1,34,34,34,1231,2321,1,}; 
    vector<string> vec_str = {"sf", "hello", "qinwen", "yan", "hello", "glasgow"}; 

    cout << "The target value " << "1" << " is "
        << count(vec.begin(), vec.end(), 1) << endl; 

    cout << "The target value " << "hello" << " is "
        << count(vec_str.begin(), vec_str.end(), "hello") << endl; 

}
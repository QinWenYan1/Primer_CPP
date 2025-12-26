#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std;

/*
* Exercise 10.27: 
* In addition to unique (§ 10.2.3, p. 384), the library
* defines function named unique_copy that takes a third iterator denoting a
* destination into which to copy the unique elements. Write a program that
* uses unique_copy to copy the unique elements from a vector into an
* initially empty list.
*/

int main(){

    vector<int> vec1 = {2331,231,32324,11,21,1212,1,11,112,313,1121,2331,231,11,11,231}; 
    vector<int> vec2; 

    sort(vec1.begin(), vec1.end());
    unique_copy(vec1.begin(), vec1.end(), back_inserter(vec2));

    for (const auto & e : vec2) cout << e << " "; 
    cout << endl; 

}
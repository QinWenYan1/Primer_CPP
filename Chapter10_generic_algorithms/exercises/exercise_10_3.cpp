#include <iostream>
#include <numeric>
#include <vector>

/*
* Exercise 10.3: 
* Use accumulate to sum the elements in a vector<int>
*/

using namespace std; 

int main(){

    vector<int> vec = {12,13,24,453,2342}; 
    cout << "The total sum of the vector is: " << accumulate(vec.cbegin(), vec.cend(), int(0)); 

}
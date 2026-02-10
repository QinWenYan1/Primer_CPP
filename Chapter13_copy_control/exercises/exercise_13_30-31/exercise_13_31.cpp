/*
* Exercise 13.31: 
* Give your class a < operator and define a vector of
* HasPtrs. 
* Give that vector some elements and then sort the vector.
* Note when swap is called.
*/

#include "HasPtr.h"
#include <iostream>
#include <vector>


using namespace std; 

int main(){

    vector<HasPtr> vec = {HasPtr("4"), HasPtr("1"), HasPtr("2"), HasPtr("4")}; 
    sort(vec.begin(), vec.end()); 

    //打印
    for (const auto e: vec) cout << e.getString() << endl; 

}
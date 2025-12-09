#include <iostream>
#include <vector>
#include <list>

using std::vector; 
using std::list; 

/*
* Exercise 9.13: 
* How would you initialize a vector<double> from a
* list<int>? From a vector<int>? 
* Write code to check your answers.
*/

int main(){

    list<int> l = {1, 12, 13}; 
    vector<double> v(l.begin(), l.end()); 

    vector<int> v1 = {11145, 14, 12};
    vector<double> v2(v1.begin(), v1.end());
    

}
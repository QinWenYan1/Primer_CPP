#include <iostream>
#include <list>
#include <vector>
#include <string>

using std::list; 
using std::vector; 
using std::string; 

/*
* Exercise 9.14: 
* Write a program to assign the elements from a list of
* char* pointers to C-style character strings to a vector of strings.
*/


int main(){

    list<const char*> l_cp = {"Hello", "the", "world"};
    vector<string> v_str;
    
    v_str.assign(l_cp.begin(), l_cp.end()); 

    for(auto e: v_str){

        std::cout << e << std::endl; 
    }


}
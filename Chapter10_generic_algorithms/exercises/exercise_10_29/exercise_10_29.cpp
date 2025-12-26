#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <string>
#include <fstream>

/*
* Exercise 10.29: 
* Write a program using stream iterators to read a text file
* into a vector of strings.
*/

using namespace std; 

int main(){

    ifstream inf("text.txt");
    istream_iterator<string> is(inf); 
    istream_iterator<string> eof; 
    ostream_iterator<string> out(cout, " "); 
    vector<string> vecStr(is, eof); 

    for (const auto & e : vecStr) *out++ = e; 
    cout << endl; 

    copy(vecStr.begin(), vecStr.end(), out); 
    cout << endl; 
    
}
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using std::ifstream; 
using std::vector;
using std::istringstream; 
using std::string; 
using std::cout; 
using std::endl; 

/*
* Exercise 8.10: 
* Write a program to store each line from a file in a
* vector<string>. Now use an istringstream to read each element from
* the vector a word at a time.
*/

int main(){

    ifstream input("test.txt"); 
    string line;
    vector<const string> lines; 

    while(getline(input, line)){ lines.push_back(line); }

    for (const auto entry: lines){

        istringstream stringLine(entry);
        string word; 
        while(stringLine >> word){ cout << word << " "; }
        cout << endl; 

    }


}
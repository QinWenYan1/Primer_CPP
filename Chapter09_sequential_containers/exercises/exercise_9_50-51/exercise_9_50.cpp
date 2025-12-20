#include <iostream>
#include <vector>

/*
* Exercise 9.50: 
* Write a program to process a vector<string>s whose
* elements represent integral values. Produce the sum of all the elements in
* that vector. Change the program so that it sums of strings that represent
* floating-point values.
*/

using namespace std; 

int main(){

    vector<string> vs = {"3", "k = -3", "115", "114514"};
    double sum = 0; 
    string pattern = "+-.1234567890"; 

    for (const auto e: vs){

        double elem = stod(e.substr(e.find_first_of(pattern))); 
        sum += elem; 

    }

    cout << sum << endl; 
}
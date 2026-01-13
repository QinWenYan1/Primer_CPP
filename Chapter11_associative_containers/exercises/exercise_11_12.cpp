#include <utility>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
* Exercise 11.12: 
* Write a program to read a sequence of strings and ints,
* storing each into a pair. Store the pairs in a vector.
*/

int main(){

    string word; 
    int count; 
    vector<pair<string, int>> vofP; 

    while( cin >> word ){

        if (!(cin >> count))  count = 0; 

        vofP.push_back(pair<string, int>(word, count)); 

    }

    //print it out
    for( const auto & e: vofP ){

        cout << e.first << "'s frequency: " << e.second << endl; 

    }
    

}
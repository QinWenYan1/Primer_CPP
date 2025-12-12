#include <list>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

/*
* Exercise 9.20: 
* Write a program to copy elements from a list<int> into
* two deques. The even-valued elements should go into one deque and the
* odd ones into the other.
*/

int main(){

    list<int> list_i = {1,2,3,4,5121,13,1145}; 
    deque<int> seq_even, seq_odd; 

    for(auto e: list_i){

        if(e%2 == 0) seq_even.push_back(e);
        else seq_odd.push_back(e); 

    }

    for(auto e: seq_even) cout << e << " "; 

}
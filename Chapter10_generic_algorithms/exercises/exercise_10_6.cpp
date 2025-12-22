#include <numeric>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std; 

/*
* Exercise 10.6: 
* Using fill_n, write a program to set a sequence of int
* values to 0.
*/

int main(){

    vector<int> vi = {132,13224,3134,134567,12367}; 
    int arr[3] = {12, 134,90};  
    vector<int> emptyV; 

    fill_n(vi.begin(), vi.size(), 0); 
    fill_n(begin(arr), sizeof(arr)/sizeof(int), 0); 
    fill_n(back_inserter(emptyV), 4, 15); 

    for(const auto e : vi) cout << e << " "; 
    cout << endl; 
    for(const auto e : arr) cout << e << " "; 
    cout << endl; 
    for(const auto e : emptyV) cout << e << " "; 
    cout << endl; 

}
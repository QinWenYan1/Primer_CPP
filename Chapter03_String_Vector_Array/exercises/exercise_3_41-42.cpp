#include <iostream>
#include <vector>
#include <iterator>

/*
* Exercise 3.41: 
* Write a program to initialize a vector from an array of ints.
*/

/*
* Exercise 3.42: 
* Write a program to copy a vector of ints into an array of ints.
*/

using std::cout;
using std::cin;
using std::endl;
using std::string; 
using std::vector; 
using std::begin;
using std::end; 


int main(void){

    //now we first initilize an integer vector from array
    vector<int> v{1,2,3,4,5};
    int arr[5] = {5,6,7,8,9};
    vector<int> v2(begin(arr), end(arr)); 

    //print outcome 
    cout << "The outcome is .... " << endl; 
    for (int e : v){ cout << e; }
    cout << endl; 
    for (int e : v2){ cout << e; }
    cout << endl;

    //now we initialize integer array from vector
    vector<int> v3(10, 1); 

    //initialize it 
    int arr1 [10]; 
    for (int i = 0; i != 10 - 1; i++){

        arr1[i] = v3[i];

    }

    //now print it right now 
    cout << "The outcome is .... " << endl;
    for (int e : v3){ cout << e; }
    cout << endl;


}
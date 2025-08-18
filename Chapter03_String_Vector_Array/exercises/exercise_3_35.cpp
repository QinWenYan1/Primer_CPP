#include <iostream>
#include <iterator>

using std::begin;
using std::end;  
using std::cout;
using std::cin;
using std::endl;

/*
* Exercise 3.35: 
* Using pointers, write a program to set the elements in an
* array to zero.
*/

int main(void){

    //define a default array whose element value is 0 
    int arr[10] = {};

    //define off-the-end pointer
    int *pend = end(arr);

    //let's traverse them 
    for(int *pbegn = begin(arr); pbegn != pend; pbegn++){

        (*pbegn) = 1; 

    }

    //let's check the outcome rn 
    cout << "The outcome is ....." << endl; 
    for(int e : arr){

        cout << e;

    }
    
    cout << endl; 

}
#include <iostream>
#include <cstddef>

using std::endl;
using std::cout;
using std::cin;
using std::vector;

/*
* Exercise 3.31: 
* Write a program to define an array of ten ints. Give each
* element the same value as its position in the array.
* Exercise 3.32: 
* Copy the array you defined in the previous exercise into
* another array. Rewrite your program to use vectors.
*/

int main(void){

    
    int arr[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    //now we copy this array into another one
    //default initialise
    int arr1[10] = {}; 

    for(size_t i = 0; i < 10; i++){
        
        arr1[i] = arr[i];
        
    }

    vector<int> v(10, 1);
    vector<int> v1 = v; 

    cout << "Finish! " << endl;

}
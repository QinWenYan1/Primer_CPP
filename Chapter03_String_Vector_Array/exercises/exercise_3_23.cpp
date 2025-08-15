#include <iostream>
#include <vector>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::string;

/*
* Exercise 3.23: 
* Write a program to create a vector with ten int elements.
* Using an iterator, assign each element a value that is twice its current value.
* Test your program by printing the vector.
*/

int main(void){

    //create integer container
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    int temp =0;

    //twice them
    for( auto iter = v.begin(); iter != v.end(); iter++){

        *iter = 2 * (*iter); 
         
    }

    //now print all of them
    cout << "Outcome: " << endl; 
    for( auto iter = v.begin(); iter != v.end(); iter++){

        cout << (*iter) << " "; 

    }

    cout << endl; 

}
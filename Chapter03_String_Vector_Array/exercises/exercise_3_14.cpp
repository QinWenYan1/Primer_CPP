#include <iostream>
#include <vector>


/*
* Exercise 3.14: 
* Write a program to read a sequence of ints from cin and
* store those values in a vector.
*/


using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(void){

    //create integer container 
    vector<int> v; 
    int temp = 0; 


    //input prompt 
    cout << "please input series of integers below:" <<endl; 
    while( cin >> temp ){

        v.push_back(temp);

    }

    //now list all elements
    cout << "the outcome: " << endl; 
    for(int element : v){
        cout << element << endl; 
    }

}
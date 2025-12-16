#include <iostream>
#include <vector>

using namespace std;

/*
* Exercise 9.38: 
* Write a program to explore how vectors grow in the library you use.
* 经过实验，是指数级别增长
*/

int main(){

    vector<int> vec; 

    for(size_t i = 0; i < 10; ++i){

        vec.push_back(i); 
        cout << "vec's size: " << vec.size() << endl; 
        cout << "vec's capacity: " << vec.capacity() << endl; 

    }
    vec.reserve(50); 
    cout << "vec's final capacity: " << vec.capacity() << endl; 

}
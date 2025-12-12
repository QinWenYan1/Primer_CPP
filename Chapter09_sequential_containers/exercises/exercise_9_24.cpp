#include <vector>
#include <iostream>

/* Exercise 9.24:
* Write a program that fetches the first element in a vector
* using at, the subscript operator, front, and begin. Test your program on
* an empty vector
*/

using namespace std;

int main(){

    vector<int> v = {1145, 15614, 2349}; 
    vector<int> v_empty; 

    cout << v.front() << endl; 
    cout << v.back() << endl; 

    cout << v.at(0) << endl; 
    cout << v_empty.at(0) << endl; //throw exception

}
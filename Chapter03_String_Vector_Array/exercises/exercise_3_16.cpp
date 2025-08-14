#include <iostream>
#include <vector>


/*
* Exercise 3.16: 
* Write a program to print the size and contents of the
* vectors from exercise 3.13. Check whether your answers to that exercise
* were correct. If not, restudy § 3.3.1 (p. 97) until you understand why you
* were wrong.
*/

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl; 


int main(void){

    vector<int> v1;                                                            
    vector<int> v2(10);                                      
    vector<int> v3(10, 42);                            
    vector<int> v4{10};                      
    vector<int> v5{10, 42};                           
    vector<string> v6{10};       
    vector<string> v7{10, "hi"};

    cout << "the size is: " << v1.size() << endl;
    cout << "the size is: " << v2.size() << " with value " << v2[0] << endl;
    cout << "the size is: " << v3.size() << " with value " << v3[0] << endl;
    cout << "the size is: " << v4.size() << " with value " << v4[0] << endl;
    cout << "the size is: " << v5.size() << "with value " << v5[0] << " " << v5[1] << endl;
    cout << "the size is: " << v6.size() << " with value " << v6[0] << endl;
    cout << "the size is: " << v7.size() << " with value " << v7[0] << endl;

}
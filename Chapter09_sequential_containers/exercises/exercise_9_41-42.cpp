#include <string>
#include <vector>
#include <iostream>

/*
* Exercise 9.41: 
* Write a program that initializes a string from a
* vector<char>.
*
* Exercise 9.42: 
* Given that you want to read a character at a time into a
* string, and you know that you need to read at least 100 characters, how
* might you improve the performance of your program?
*
*
* Answer: 
* 由于我们知道起码这个string得有100个字符，那么我们可以
* 将string变量提前提升为100个char的capacity通过使用reserve
* 这样就不需要再去无意义的提升capacity
*/
using namespace std;

//Exercise 9.42

int main(){

    vector<char> vc = {'h','d','c'};
    string s_c; 

    s_c.reserve(100);

    for (const auto c:vc) s_c.push_back(c);

    cout << s_c << endl; 
    cout << s_c.capacity() << endl; 

}
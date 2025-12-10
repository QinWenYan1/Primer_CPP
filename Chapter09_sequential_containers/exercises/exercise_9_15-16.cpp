#include <iostream>
#include <vector>
#include <list>

using namespace std;

/*
* Exercise 9.15: 
* Write a program to determine whether two vector<int>s are equal.
* 
* Exercise 9.16: 
* Repeat the previous program, but compare elements in a
* list<int> to a vector<int>.
*/

int main(){

    vector<int> v1={1145, 12, 15};
    vector<int> v2={514, 140, 240}; 
    vector<int> v3={514, 220, 318}; 
    list<int> l1 = {1145, 12, 15};

    cout << "Start comparison ..." << endl; 
    cout << (v1 > v2) << endl;
    cout << (v3 < v2) << endl;
    //cout << (l1 == v1) << endl; error: 无法比较 - 必须保证类型要完全相同

}
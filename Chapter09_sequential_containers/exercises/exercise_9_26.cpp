#include <iostream>
#include <list>
#include <vector>
#include <iterator>

/*
* Exercise 9.26: 
* Using the following definition of ia, copy ia into a vector
* and into a list. Use the single-iterator form of erase to remove the
* elements with odd values from your list and the even values from your
* vector.
* int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
*/

using namespace std; 

int main(){

    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 }; 

    vector<int> iv(begin(ia), end(ia)); 
    list<int> il(begin(ia), end(ia)); 

    /*----start with vector----*/
    auto head = iv.begin(); 
    auto tail = iv.end(); 
    while(head != tail){

        if(*head % 2 == 0 ) head = iv.erase(head); 
        else ++ head; 

    }

    /*----start with list----*/
    auto lhead = il.begin(); 
    auto ltail = il.end(); 
    while(lhead != ltail){

        if(*lhead % 2 != 0 ) lhead = il.erase(lhead); 
        else ++ lhead; 

    }

    for (const auto e:iv) cout << e << " ";
    cout << endl; 

    for (const auto e:il) cout << e << " ";
    cout << endl; 

}
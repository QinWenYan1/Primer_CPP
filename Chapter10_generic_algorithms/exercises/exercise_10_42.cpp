#include <iostream>
#include <list>
#include <numeric>

using namespace std; 

/*
* Exercise 10.42: 
* Reimplement the program that eliminated duplicate words
* that we wrote in § 10.2.3 (p. 383) to use a list instead of a vector.
*/

inline list<int> &elimDups(list<int>& l){

    l.sort();
    l.unique(); 

    return l; 

}

int main(){

    list<int> l = {1234, 53, 34395, 13, 1234, 134,5, 13, 13, 13}; 

    elimDups(l); 
    for (const auto e : l) cout << e << endl; 


}
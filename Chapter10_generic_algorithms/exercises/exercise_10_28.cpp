#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
#include <numeric>

using namespace std; 

/*
* Exercise 10.28: 
* Copy a vector that holds the values from 1 to 9 inclusive,
* into three other containers. Use an inserter, a back_inserter, and a
* front_inserter, respectivly to add elements to these containers. Predict
* how the output sequence varies by the kind of inserter and verify your
* predictions by running your programs.
*/

int main(){

    vector<int> vec = {1,2,3,4,5,6,7,8,9};
    list<int>  list; //for front_inserter
    deque<int> que; //for back_inserter
    vector<int> vect; //for inserter

    copy(vec.cbegin(), vec.cend(), back_inserter(list)); // {1,2,3,4,5,6,7,8,9}
    copy(vec.cbegin(), vec.cend(), front_inserter(que)); // {9,8,7,6,5,4,3,2,1}
    copy(vec.cbegin(), vec.cend(), inserter(vect, vect.begin())); // {1,2,3,4,5,6,7,8,9}

    for(const auto e : list) cout << e << ","; 
    cout << endl; 

    for(const auto e : que) cout << e << ","; 
    cout << endl; 

    for(const auto e : vect) cout << e << ","; 
    cout << endl; 


}
#include <deque>
#include <list>

using std::deque;
using std::list; 

/*
* Exercise 9.2: 
* Define a list that holds elements that are deques that hold ints.
*/

int main(){

    list <deque<int>> listOfDeque;
    deque <int> d(10, 1);
    listOfDeque.emplace_back(d); 

}
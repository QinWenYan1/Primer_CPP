#include <vector>
#include <iterator>
#include <numeric>
#include <iostream>
#include <list>

using namespace std;

/*
* Exercise 10.34: 
* Use reverse_iterators to print a vector in reverse
* order.
*
* Exercise 10.35: 
* Now print the elements in reverse order using ordinary
* iterators.
*
* Exercise 10.36: 
* Use find to find the last element in a list of ints with
* value 0.
*
* Exercise 10.37: 
* Given a vector that has ten elements, copy the elements
* from positions 3 through 7 in reverse order to a list.
*/

int main(){

    vector<int> vec = {1,2,3,4,0,5,6,7,8,9};
    ostream_iterator<int> outputIter(cout, " "); 
    list<int> list; 
    


    cout << "Using reversed iterator printing ..." << endl; 
    copy(vec.crbegin(), vec.crend(), outputIter);
    cout << endl; 

    cout << "Using original iterator printing ..." << endl; 
    for (auto i = vec.cend()-1; i >= vec.begin(); --i ){
        cout << *i << " "; 
    }
    cout << endl; 

    cout << "Using find to locate the last 0 element in the vector ..." << endl; 
    auto target = find(vec.crbegin(), vec.crend(), 0);
    cout << "The outcome is: " << (vec.cend() - target.base() - 1) << endl;
    
    copy(vec.cbegin()+3, vec.cbegin()+8, front_inserter(list));
    copy(list.cbegin(), list.cend(), outputIter); 
    cout << endl; 
    
}
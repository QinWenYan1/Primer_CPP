#include <iostream>
#include <vector>
#include <numeric>

/*
* Exercise 10.30: 
* Use stream iterators, sort, and copy to read a sequence
* of integers from the standard input, sort them, and then write them back to
* the standard output.
*
* Exercise 10.31: 
* Update the program from the previous exercise so that it
* prints only the unique elements. Your program should use unqiue_copy (§
* 10.4.1, p. 403).
*/


using namespace std; 

int main(){

    istream_iterator<int> input(cin);
    istream_iterator<int> end; 
    ostream_iterator<int> output(cout, " "); 
    vector<int> vec(input, end); 

    sort(vec.begin(), vec.end());

    unique_copy(vec.begin(), vec.end(), output); 
    cout << endl; 

}
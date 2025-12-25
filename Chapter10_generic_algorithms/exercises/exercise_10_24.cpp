#include <iostream>
#include <numeric>
#include <vector>
#include <string>

/*
* Exercise 10.24: 
* Use bind and check_size to find the first element in a
* vector of ints that has a value greater than the length of a specified
* string value.
*/

using namespace std; 
using std::placeholders::_1; 

inline size_t readString(const string & str) { return str.size(); }

inline vector<int> &sortIt(vector<int> & vec){

    sort(vec.begin(), vec.end()); 
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); 
    return vec; 

}

bool check_size(const int &s, const size_t &sz){ return s > sz; }

int main(){

    string speStr = "Qinwen yan"; 
    size_t searchSize = readString(speStr);
    vector<int> vecI = {2,3,4,5,6,7,8,9,1,2,33,2,44,3,2,5,64,3,3,34}; 
    sortIt(vecI);
    auto target = find_if(vecI.begin(), vecI.end(), bind(check_size, _1, searchSize));

    cout << "The first element in the vector greater the length of string " << speStr 
        << " is " << *target << endl; 

}
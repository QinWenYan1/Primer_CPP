#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <functional>

/*
* Exercise 10.25: 
* In the exercises for § 10.3.2 (p. 392) you wrote a version
* of biggies that uses partition. Rewrite that function to use
* check_size and bind.
*/

using namespace std; 
using std::placeholders::_1; 

inline vector<string> &elimDups(vector<string>& vec){

    sort(vec.begin(), vec.end(), [](const string & str1, const string &str2){ return str1 < str2; });
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); 

    return vec; 

}

inline bool check_size(const string& str, size_t length){ return str.size() >= length; }

void biggies(vector<string> & targetVec, size_t length){

    elimDups(targetVec); 
    stable_sort(targetVec.begin(), targetVec.end(), [](const string & str1, const string &str2){ return str1.size() < str2.size(); });

    auto beginIter = stable_partition(targetVec.begin(),targetVec.end(), bind(check_size, _1, length)); 
    size_t freq = count_if(targetVec.begin(), beginIter, [length](const string & target){ return  length < target.size(); }); 

    cout << "The frequency of the strings with length greater than " << length << " is: " << freq;

}


int main(){

    vector<string> vecStr = {
            "This", "Hello", "kill", "bill",
            "world", "Qinwen Yan", "Gethin",
            "Allen", "spml", "april", "yes",
            "lab", "of", "one", "Y"
            }; 

    biggies(vecStr, 5); 
    
}
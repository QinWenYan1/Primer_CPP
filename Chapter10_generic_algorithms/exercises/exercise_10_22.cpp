#include <iostream>
#include <numeric>
#include <vector>
#include <string>

/*
* Exercise 10.22: 
* Rewrite the program to count words of size 6 or less using
* functions in place of the lambdas.
*/

using namespace std; 
using std::placeholders::_1; 

inline vector<string> &elimDups(vector<string>& vec){

    sort(vec.begin(), vec.end(), [](const string & str1, const string &str2){ return str1 < str2; });
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); 

    return vec; 

}

int compareLen(const string& str, size_t size){ return  size >= str.size(); }

void biggies(vector<string> & targetVec, size_t length){
    elimDups(targetVec); 
    stable_sort(targetVec.begin(), targetVec.end(), [](const string & str1, const string &str2){ return str1.size() < str2.size(); });

    auto beginIter = stable_partition(targetVec.begin(),targetVec.end(), [length](const string& str){ return str.size() >= length; }); 
    size_t freq = count_if(targetVec.begin(), beginIter, bind(compareLen, _1, length)); 

    cout << "The frequency of the strings with length greater than " << length << " is: " << freq;

}


int main(){

    vector<string> vecStr = {
            "This", "Hello", "kill", "bill",
            "world", "Qinwen Yan", "Gethin",
            "Allen", "spml", "april", "yes",
            "lab", "of", "one", "Y"
            }; 

    biggies(vecStr, 6); 
    
}
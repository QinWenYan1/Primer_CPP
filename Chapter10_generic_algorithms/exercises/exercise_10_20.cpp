#include <iostream>
#include <numeric>
#include <vector>
#include <string>

/*
* Exercise 10.20: 
* The library defines an algorithm named count_if. Like
* find_if, this function takes a pair of iterators denoting an input range and
* a predicate that it applies to each element in the given range. count_if
* returns a count of how often the predicate is true. Use count_if to rewrite
* the portion of our program that counted how many words are greater than
* length 6
*/

using namespace std; 

inline vector<string> &elimDups(vector<string>& vec){

    sort(vec.begin(), vec.end(), [](const string & str1, const string &str2){ return str1 < str2; });
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); 

    return vec; 

}

void biggies(vector<string> & targetVec, size_t length){
    elimDups(targetVec); 
    stable_sort(targetVec.begin(), targetVec.end(), [](const string & str1, const string &str2){ return str1.size() < str2.size(); });

    auto beginIter = stable_partition(targetVec.begin(),targetVec.end(), [length](const string& str){ return str.size() >= length; }); 
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
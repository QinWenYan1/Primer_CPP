#include <iostream>
#include <vector>
#include <string>

using namespace std; 

/*
* Exercise 10.16: 
* Write your own version of the biggies function using
* lambdas.
*/


inline vector<string> &elimDups(vector<string>& vec){

    sort(vec.begin(), vec.end(), [](const string & str1, const string &str2){ return str1 < str2; });
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); 

    return vec; 

}

void biggies(vector<string> & targetVec, size_t length){
    elimDups(targetVec); 
    stable_sort(targetVec.begin(), targetVec.end(), [](const string & str1, const string &str2){ return str1.size() < str2.size(); });

    auto beginIter = find_if(targetVec.begin(),targetVec.end(), [length](const string& str){ return str.size() >= length; }); 
    for_each(beginIter, targetVec.end(), [](const string & target){ cout << target << endl; }); 

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
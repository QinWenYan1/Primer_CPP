#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/*
* Exercise 10.11: 
* Write a program that uses stable_sort and isShorter
* to sort a vector passed to your version of elimDups. 
* Print the vector to
* verify that your program is correct
*/

bool is_shorter(int v1, int v2){ return v1 < v2;}

inline vector<int> &elimDups(vector<int>& vec){

    stable_sort(vec.begin(), vec.end(), is_shorter);
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); 

    return vec; 

}

int main(){

    vector<int> vec = {1234, 53, 34395, 13, 1234, 134,5, 13, 13, 13}; 

    elimDups(vec); 
    for (const auto e : vec) cout << e << endl; 


}

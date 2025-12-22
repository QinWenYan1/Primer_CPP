#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/*
* Exercise 10.9: 
* Implement your own version of elimDups. Test your
* program by printing the vector after you read the input, 
* after the call to
* unique, and after the call to erase.
*/

inline vector<int> &elimDups(vector<int>& vec){

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); 

    return vec; 

}

int main(){

    vector<int> vec = {1234, 53, 34395, 13, 1234, 134,5, 13, 13, 13}; 

    elimDups(vec); 
    for (const auto e : vec) cout << e << endl; 


}

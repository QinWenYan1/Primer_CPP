#include <map>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std; 

/*
* Exercise 11.16: 
* Using a map iterator write an expression that assigns a
* value to an element.
*/

int main(){

    vector<int> v = {1,1145,14};
    map<int, int> mi = {{0,0}, {1,0}, {2,0}}; 
    int i = 0; 

    for (auto iter = mi.begin(); iter != mi.end(); ++iter){

        iter->second = v[i]; 
        ++ i; 

    }

    for ( const auto e: mi ) cout << e.first << " : " << e.second << endl;

}
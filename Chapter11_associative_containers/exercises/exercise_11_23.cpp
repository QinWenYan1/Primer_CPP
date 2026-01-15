#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std; 


/*
* Exercise 11.23: 
* Rewrite the map that stored vectors of children’s names
* with a key that is the family last name for the exercises in § 11.2.1 (p. 424)
* to use a multimap.
*/

int main(){

    string p; 
    string child; 

    multimap<string, string> fams; 

    while( cin >> p ){

        if ( cin >> child ){
            auto ret = fams.emplace(p, child);
        }

    }

    for ( const auto & e: fams ){
        cout << e.first << " has children: "; 
        cout << e.second;  
        cout << endl; 
    }

}
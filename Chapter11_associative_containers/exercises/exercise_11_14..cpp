#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <numeric>
#include <utility>

using namespace std; 

/*
* Exercise 11.14: 
* Extend the map of children to their family name that you
* wrote for the exercises in § 11.2.1 (p. 424) by having the vector store a
* pair that holds a child’s name and birthday.
*/


int main(){

    string p; 
    string child; 

    map<string, vector<pair<string, int>>> fams;
    ostream_iterator<string> output(cout, " "); 
    while( cin >> p ){

        if ( cin >> child ){
            auto inserter = back_inserter(fams[p]);
            int birth = 0; 
            if (!(cin >> birth)) birth = 0; 
            *inserter = {child, birth}; 
        }

    }

    for ( const auto & e: fams ){
        cout << e.first << " has children: " << endl; 
        for (const auto & ee : e.second) cout << "  " <<  ee.first << " having " << ee.second << " Years old" << endl;
    }

}
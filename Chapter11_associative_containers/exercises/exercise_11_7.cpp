#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std; 

/*
* Exercise 11.7: 
* Define a map for which the key is the family’s last name and
* the value is a vector of the children’s names. Write code to add new
* families and to add new children to an existing family.
*/

/*
* Exercise 11.8: 
* Write a program that stores the excluded words in a vector
* instead of in a set. What are the advantages to using a set?
*/

int main(){

    string p; 
    string child; 

    map<string, vector<string>> fams;
    ostream_iterator<string> output(cout, " "); 
    while( cin >> p ){

        if ( cin >> child ){
            auto inserter = back_inserter(fams[p]);
            *inserter = child; 
        }

    }

    for ( const auto & e: fams ){
        cout << e.first << " has children: "; 
        copy((e.second).begin(),(e.second).end(), output );  
        cout << endl; 
    }

}
#include <iostream>
#include <map>
#include <string>

using namespace std; 


/*
* Exercise 11.31: 
* Write a program that defines a multimap of authors and
* their works. Use find to find an element in the multimap and erase that
* element. Be sure your program works correctly if the element you look for is
* not in the map.
*/

/*
* Exercise 11.32: 
* Using the multimap from the previous exercise, write a
* program to print the list of authors and their works alphabetically.
*/

int main(){

    multimap<string, string> authorsTable = 
        { 
            {"qinwen", "1145"},
            {"yan", "1145-14"}, 
            {"gethin", "0205"}, 
            {"Norman", "510"},
            {"qinwen", "2974"}, 
            {"qinwen", "224"}, 
            {"zenith", "91"}
        }; 
    
    auto iter = authorsTable.find("qinwen");
    size_t entries = authorsTable.count("qinwen"); 
    
    cout << "deleting author qinwen infor: " << endl; 
    while (entries){

        cout << "deleting " << iter->second << endl; 
        iter =  authorsTable.erase(iter); 
        -- entries; 

    }

    for ( const auto e: authorsTable ){

        cout << e.first << " Has " << e.second << endl; 

    }

}
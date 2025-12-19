#include <string>
#include <iostream>

using namespace std; 

/*
* Exercise 9.47: 
* Write a program that finds each numeric character and then
* each alphabetic character in the string "ab2c3d7R4E6". Write two
* versions of the program. The first should use find_first_of, and the
* second find_first_not_of.
*/

inline void find_numeric_operation(string str){

    string pattern("1234567890"); 
    string::size_type pos = 0, tail = str.size(); 
    
    cout << "find_first_of version ..." << endl; 
    while( pos != tail && pos != string::npos ){

        auto first = str.find_first_of(pattern, pos); 

        while( pos != first && pos < tail ){ cout << "Alpha: " << str[pos++] << endl; }

        if (pos != tail) cout << "Num: " << str[pos++] << endl;

    }

}

inline void find_not_numeric_operation(string str){

    string pattern("1234567890"); 
    string::size_type start = 0, tail = str.size(); 
    
    cout << "find_first_not_of version ..." << endl; 
    while( start != tail && start != string::npos ){

        auto first = str.find_first_not_of(pattern, start); 

        while( start != first && start < tail ){ cout << "Num: " << str[start++] << endl; }

        if (start != tail) cout << "Alpha: " << str[start++] << endl; 
        

    }

}

int main(){

    string name("ab2c3d7R4E6");
    find_numeric_operation(name); 
    find_not_numeric_operation(name); 

}
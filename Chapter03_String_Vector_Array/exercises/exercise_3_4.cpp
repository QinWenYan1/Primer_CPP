#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
* Exercise 3.4:
* Write a program to read two strings and report whether the
* strings are equal. If not, report which of the two is larger. Now, change
* the program to report whether the strings have the same length, and if
* not, report which is longer.
*/


int main(void){

    string s1; 
    string s2;
    
    // read input and store into two strings
    cin >> s1 >> s2; 

    //now compare
    if(s1.size() == s2.size()){

        cout << "yes, they have identical size" << endl;

    }else{

        if( s1.size() > s2.size() ){

            cout << "The string - " << s1 << " - is longer" << endl; 
            return 0;  
        }

        cout << "The string - " << s2 << " - is longer" << endl;

    }
    return 0; 
}
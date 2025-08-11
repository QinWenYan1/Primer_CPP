#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string; 

/*
* Exercise 3.2: 
* Write a program to read the standard input a line at a time.
* Modify your program to read a word at a time.
*
*/

int print_line(void){

    // define the target line 
    string line;
    
    //read input line by line until end-of-file
    while(getline(cin, line)){
        if(!line.empty()){
            //print string line by line 
            cout << line << endl; 
        }
    }

    return 0; 

}

int main(void){

    string word;

    //read input word by word
    while(cin >> word){

        //print string owrd by word
        cout << word << endl; 

    }

    return 0; 

}
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <map>

/*
* Exercise 11.3: 
* Write your own version of the word-counting program.
*
* Exercise 11.4: 
* Extend your program to ignore case and punctuation. For
* example, “example.” “example,” and “Example” should all increment the same
* counter.
*/

using namespace std; 



int main(){

    map<string, size_t> wordsTable; 
    string excluded = ",./!@£$%^&*()'\\|?><\"";
    ifstream inputFile("input.txt"); 
    istream_iterator<string> ins(inputFile), eof; 

    while(ins != eof ){

        string temp = *ins++;
        size_t end = temp.find_first_of(excluded);  
        if(temp.find_first_of(excluded) == string::npos) end = temp.size();
        ++ wordsTable[temp.substr(0, end)]; 
    
    }

    for( const auto &e : wordsTable ) cout << e.first << " occurs " << e.second << endl; 

}
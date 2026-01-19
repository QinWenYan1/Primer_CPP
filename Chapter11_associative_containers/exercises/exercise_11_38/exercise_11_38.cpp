#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <map>

/*
* Exercise 11.38: 
* Rewrite the word-counting (§ 11.1, p. 421) and word-
* transformation (§ 11.3.6, p. 440) programs to use an unordered_map.
*/

using namespace std; 

int main(){

    unordered_map<string, size_t> wordsTable; 
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
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <map>

/*
* Exercise 11.20: 
* Rewrite the word-counting program from § 11.1 (p. 421) to
* use insert instead of subscripting. Which program do you think is easier to
* write and read? Explain your reasoning.
*
*
* Answer: 我认为使用下标更好， 代码更简洁
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
        auto ret = wordsTable.emplace(temp.substr(0,end), 1);
        if (!(ret.second)) ++ ret.first->second; 
        
    
    }

    for( const auto &e : wordsTable ) cout << e.first << " occurs " << e.second << endl; 

}
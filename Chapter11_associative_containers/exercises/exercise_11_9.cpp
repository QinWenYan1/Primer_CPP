#include <map>
#include <iostream>
#include <list>
#include <iterator>


using namespace std;

/*
* Exercise 11.9: 
* Define a map that associates words with a list of line
* numbers on which the word might occur.
*/

int main(){

    //create the table to looking for words in the processing

    map<string, list<int>> table; 
    string word; 
    int nline = 1; 
    
    istream_iterator<string> in_iter(cin), eof;
    while(in_iter != eof){
        table[*in_iter++].push_back(nline++);
    }

    //print it out
    for (const auto &e : table){

        cout << e.first << " appears in the lines: "; 
        for (const auto & ee: e.second){

            cout << ee << " ";

        }
        cout << endl; 

    }

}
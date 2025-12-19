#include <string>
#include <fstream>
#include <iostream>

using namespace std; 

/*
* Exercise 9.49: 
* A letter has an ascender if, as with d or f, part of the letter
* extends above the middle of the line. A letter has a descender if, as with p or
* g, part of the letter extends below the line. Write a program that reads a file
* containing words and reports the longest word that contains neither
* ascenders nor descenders.
*/

int main(){

    ifstream fileStream("./file.txt");
    string word; 
    string nonDeAscender("aceimnorsuvwxz"); 
    vector<string> words; 
    string theLongest; 

    while(fileStream >> word) words.push_back(word);

    //find the longest one
    for(const auto e : words){
        auto outcome = e.find_first_not_of(nonDeAscender); 
        if (outcome == string::npos){
            theLongest = (theLongest.size() < e.size() )? e : theLongest; 
        } 
    }

    cout << "The longest word: " << theLongest << endl; 

}
#include <iostream> //use cout, cin, endl 
#include <fstream> //use ifstream
#include <string> //use string 
#include <set> // use set 
#include "TextQuery.h" // use TextQuery 
#include <iterator> // use ostream_iterator

using std::ifstream; 
using std::cout; 
using std::string; 
using std::cin; 
using std::endl; 
using std::set; 


std::ostream &print(std::ostream &output, const QueryResult &outcome){

    std::ostream_iterator<size_t> o(output, " "); 
    for (const auto e : outcome.getResult()){ o = (e+1);}
    return output; 

}

void runQueries(ifstream &infile)
{
    // infile is an ifstream that is the file we want to query
    TextQuery tq(infile); // store the file and build the query map
    // iterate with the user: prompt for a word to find and print results
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        // stop if we hit end-of-file on the input or if a 'q' is entered
        if (!(cin >> s) || s == "q") break;
        // run the query and print the results
        print(cout, tq.query(s)) << endl;
    }

}

int main(){

    ifstream in("input.txt"); 
    runQueries(in); 

}
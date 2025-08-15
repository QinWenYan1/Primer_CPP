#include <iostream>
#include <vector>

using std::cout; 
using std::cin; 
using std::endl;
using std::string;
using std::vector; 

/*
* Exercise 3.21: 
* Redo the first exercise from § 3.3.3 (p. 105) using iterators.
*/

int main(void){

    //create a string container with capacity 8 words 
    vector<string> words;
    string temp; 

    //input word into container
    cout << "input your words: " << endl;  
    while( cin >> temp ){ words.push_back(temp); }

    //now print all words line by line
    int flag = 0; 
    for( auto iter = words.begin(); iter != words.end(); iter++ ){

        if( flag == 8 ){ 

            
            cout << endl;
            cout << *iter << " "; 
            flag = 1; 

        }else{

            cout << *iter << " ";
            flag ++; 

        }

    }

    cout << endl; 

    cout << "printing terminates..... " << endl; 


}
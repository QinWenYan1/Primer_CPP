#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string; 

/*
* Exercise 3.5: 
* Write a program to read strings from the standard input,
* concatenating what is read into one large string. Print the concatenated
* string. Next, change the program to separate adjacent input strings by a
* space.
*/

int main(void){

    string word;
    string large_word; 

    //read input word by word
    while(cin >> word){

        //concatenate them with a seperated space
        large_word += (word + " "); 

    }

    cout << large_word << endl; 

    return 0; 

}
#include <iostream>
#include <vector>

/*
* Exercise 3.17: 
* Read a sequence of words from cin and store the values a
* vector. After you’ve read all the words, process the vector and change
* each word to uppercase. Print the transformed elements, eight words to a
* line.
*/

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl; 

int main(void){

    //now first create fundamental container with size 8
    vector<string> strings(8); 
    string temp; 
    decltype(strings.size()) index; 

    while( cin >> temp ){
        
        //check if it's necessary to print
        if( index == 8){
            for (string word : strings){
                cout << word << " "; 
            }

            cout << endl; 
            index = 0; 
        }

        //transfer all characters to upper case 
        for(auto &c : temp){ c = toupper(c); }
        
        //store it into container
        strings[index] = temp; 

        //increment by one 
        index ++;

    }

}
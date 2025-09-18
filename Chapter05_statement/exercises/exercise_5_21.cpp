#include <iostream>
#include <string>
#include <cctype>

using std::cout;
using std::cin;
using std::endl; 
using std::string; 
using std::islower; 


/*
* Exercise 5.21: 
* Revise the program from the exercise in § 5.5.1 (p. 191) so
* that it looks only for duplicated words that start with an uppercase letter.
*/

/*
string word, pre_word; 
    bool is_repeated = false; 
    cout << "Please input your strings ..." << endl; 
    while( cin >> word ){

        if( pre_word == word ){

            cout << "The string " << word << " has been repeated ..." << endl; 
            is_repeated = true; 
            break; 

        }

        pre_word = word; 

    }

    if( !is_repeated ) cout << "There is no any string repeated ..." << endl;
 */

int main(void){

    string word, pre_word; 
    bool is_repeated = false; 
    cout << "Please input your strings ..." << endl; 
    while( cin >> word && !word.empty()){

        //我们需要检查单词是不是都是小写，也就是查word即可
        //如果不是，直接跳过这一个字符串
        if(!islower(word[0])) { pre_word = word; continue; } 

        if( pre_word == word ){

            cout << "The string " << word << " has been repeated ..." << endl; 
            is_repeated = true; 
            break; 

        }

        pre_word = word; 

    }

    if( !is_repeated ) cout << "There is no any string repeated ..." << endl;

}

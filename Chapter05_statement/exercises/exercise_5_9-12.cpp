#include <iostream>
#include <string>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::tolower; 

/*
* Exercise 5.9: 
* Write a program using a series of if statements to count the
* number of vowels in text read from cin.
*/

/*
* Exercise 5.10: 
* There is one problem with our vowel-counting program as
* we’ve implemented it: It doesn’t count capital letters as vowels. Write a
* program that counts both lower- and uppercase letters as the appropriate
* vowel—that is, your program should count both 'a' and 'A' as part of
* aCnt, and so forth.
*/

/*
* Exercise 5.11: 
* Modify our vowel-counting program so that it also counts the
* number of blank spaces, tabs, and newlines read.
*/

/*
* Exercise 5.12: 
* Modify our vowel-counting program so that it counts the
* number of occurrences of the following two-character sequences: ff, fl,
* and fi.
*/


int main(void){

    //let's input our words
    cout << "Please input something here ..." << endl; 
    string input; 
    if( !getline(cin, input) ){ cout << "unavaliable input !" << endl; return 1; } 

    //we need to convert characters in the string to lower cases 
    for (auto &e : input) e = tolower(e); 
    
    //now let's start with analysing the words in term of number of vowels 
    int acnt = 0, ecnt = 0, icnt = 0, ocnt = 0, ucnt = 0, 
    scnt = 0, tabcnt = 0, newcnt = 0, ffcnt = 0, flcnt = 0, ficnt = 0; 

    //this flag is used to note that the apprance of the f has been found 
    bool flag = false; 

    for ( const auto e: input ){
 
        if( e == 'i' ) flag = flag? (++ficnt, false): (++icnt, false); //如果f上一个已经出现过，那么ficnt+1,否则icnt+1, flag为false
        else if( e == 'f' ) flag = flag? (++ffcnt, false): true; //如果上一个是f，则ffcnt+1, 否则将flag设置为true
        else if( e == 'l' ) flag = flag? (++flcnt, false): false; //如果上一个是f，则flcnt+1, 否则flag为false
        else {

            if ( e == 'a') ++ acnt; 
            else if( e == 'e') ++ ecnt; 
            else if( e == 'o' ) ++ ocnt; 
            else if( e == 'u' ) ++ ucnt; 
            else if( e == ' ' ) ++ scnt; 
            else if( e == '\t' ) ++ tabcnt; 
            else if( e == '\n' ) ++ newcnt;
            flag = false; //断联了，重制flag

        } 
         
    }

    //now ends analysing and print out the outcome 
    cout << "let's print vowels' number in total" << endl; 
    cout << "The number of vowels a/A is: " << acnt << endl; 
    cout << "The number of vowels e/E is: " << ecnt << endl;
    cout << "The number of vowels i/I is: " << icnt << endl;
    cout << "The number of vowels o/O is: " << ocnt << endl;
    cout << "The number of vowels u/U is: " << ucnt << endl;
    cout << "The number of space is: " << scnt << endl;
    cout << "The number of tabs is: " << tabcnt << endl;
    cout << "The number of new line is: " << newcnt << endl;
    cout << "The number of ff is: " << ffcnt << endl;
    cout << "The number of fl is: " << flcnt << endl;
    cout << "The number of fi is: " << ficnt << endl;

}
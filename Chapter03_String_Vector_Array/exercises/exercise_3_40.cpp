#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::strcat; 

/*
* Exercise 3.40: 
* Write a program to define two character arrays initialized
* from string literals. Now define a third character array to hold the
* concatenation of the two arrays. Use strcpy and strcat to copy the two
* arrays into the third.
*/

int main(void){

    //define two strings 
    char str1[] = "hello";
    char str2[] = "world";
    char target[11] = {};
    
    //now we concatenate two string together into the target
    strcat(target, str1);
    strcat(target, str2); 

    cout << target << endl; 

} 
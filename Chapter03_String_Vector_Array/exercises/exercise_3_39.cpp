#include <iostream>
#include <vector>
#include <iterator>
#include <cstring>

using std::endl;
using std::cout;
using std::cin;
using std::string; 
using std::begin;
using std::end; 

/*
* Exercise 3.39: 
* Write a program to compare two strings. Now write a
* program to compare the values of two C-style character strings.
*/

int main(void){

    //compare std::string first 
    string str1 = "hello world";
    string str2 = "helloworld"; 

    if( str1 == str2 ){

        cout << "two strings are equal..." << endl;

    }else if ( str1 > str2 )
    {
        cout << "First string is bigger than second string..." << endl; 
        
    }else{

        cout << "first string is smaller than second one" << endl; 

    }

    //let's compare c-style string 
    char str3[] = "hello world";
    char str4[] = "helloworld";

    if( int d = strcmp(str3, str4) == 0 ){

        cout << "two strings are equal..." << endl;

    }else if(d > 0 ){

        cout << "First string is bigger than second string..." << endl; 

    }else{

        cout << "first string is smaller than second one" << endl; 

    }
    




}
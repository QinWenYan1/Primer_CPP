#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl; 
using std::string; 

/*
* Exercise 5.19: 
* Write a program that uses a do while loop to repetitively
* request two strings from the user and report which string is less than
* the other.
*/

int main(void){

    string command; 
    do {

        //reset command on every iteration 
        command = ""; 

        //two requested string 
        cout << "Please input two strings here ..." << endl;
        string str1, str2; 
        cin >> str1 >> str2;

        string outcome = (str1 >= str2)? (str1 + " is bigger than or equal to " + str2): 
            (str2 + " is bigger than " + str1); 

        cout << outcome << endl; 

        //then ask for repetition 
        cout << "input yes to continue, no for stopping ..." << endl; 
        cin >> command;

    }while( (!command.empty()) && (command != "no" ) );

}
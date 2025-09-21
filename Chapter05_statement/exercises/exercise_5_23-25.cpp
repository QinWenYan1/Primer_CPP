#include <iostream>
#include <stdexcept>
#include <string>

using std::cout; 
using std::cin;
using std::endl; 
using std::runtime_error; 
using std::string; 

/*
* Exercise 5.23: 
* Write a program that reads two integers from the standard
* input and prints the result of dividing the first number by the second.
* C++ Primer, Fifth Edition
* 
* Exercise 5.24: 
* Revise your program to throw an exception if the second
* number is zero. Test your program with a zero input to see what happens on
* your system if you don’t catch an exception.
* Answer: 除数为0导致的表现未定义， 可能会直接返回0，也可能导致程序直接崩溃
*
* Exercise 5.25: 
* Revise your program from the previous exercise to use a
* try block to catch the exception. The catch clause should print a message
* to the user and ask them to supply a new number and repeat the code inside
* the try.
*/

int main(void){

    int first, second;
    bool is_skipped = false; //use to decide if we need to skip assignment to first number
    cout << "Please input integer one by one ..." << endl;

    while(cin){
        try{

            if(!is_skipped) {
                cin >> first; 
            }

            cin >> second;
            is_skipped = false; 

            if (!second){
                //throw error if second number is zero
                throw runtime_error("Second one cannot be zero");

            }

            cout << "Outcome is ..." << endl; 
            cout << (first/second) << endl; 
        }catch (runtime_error err){

            cout << err.what() 
                << "\nDo you want to reinput the integer, press y/n ?" << endl; 

            char command; 
            cin >> command; 

            if(command == 'y') {
                cout << "Now input your new value ..." << endl;
                is_skipped = true; 
                continue;
            } else {

                cout << "Program terminated." << endl;
                break; 
                
            }
            
        }
    }
}

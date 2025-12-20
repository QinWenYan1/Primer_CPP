#include "Timer.h"
#include <iostream>

using namespace std; 
/*
* Exercise 9.51: 
* Write a class that has three unsigned members
* representing year, month, and day. 
* Write a constructor that takes a string
* representing a date. 
* Your constructor should handle a variety of date
* formats, such as January 1, 1900, 1/1/1900, Jan 1, 1900, and so on.
*/

int main(){

    Timer t1("January 1, 1900");
    Timer t2("1/1/1900");
    Timer t3("Jan 1, 1900");  

    cout << "t1: " << t1.get_year() << " "
         << t1.get_month() << " "
         << t1.get_date() << " " << endl; 
    
    cout << "t2: " << t2.get_year() << " "
         << t2.get_month() << " "
         << t2.get_date() << " " << endl; 
    
         cout << "t3: " << t3.get_year() << " "
         << t3.get_month() << " "
         << t3.get_date() << " " << endl; 

}
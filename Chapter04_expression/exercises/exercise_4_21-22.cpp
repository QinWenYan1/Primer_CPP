#include <iostream>
#include <vector>
#include <string>



using std::cout;
using std::cin;
using std::endl; 
using std::vector;
using std::string; 

/*
* Exercise 4.21: 
* Write a program to use a conditional operator to find the
* elements in a vector<int> that have odd value and double the value of
* each such element.
*/

/*
* Exercise 4.22: Extend the program that assigned high pass, pass, and fail
* grades to also assign low pass for grades between 60 and 75 inclusive. Write
* two versions: One version that uses only conditional operators; the other
* should use one or more if statements. Which version do you think is easier
* to understand and why?
* answer: if 版本更好， 因为可阅读性更好
*/

int main(void){

    //exercise 21
    vector<int> v {12, 12324, 100, 123, 4345, 24, 342, 433, 5};

    cout << "Detecting odd values and even values in vector ..." << endl; 

    for (int & e : v){

        e = (e % 2 == 0) ?  e : e * 2; 
        cout << "value : "  << e << endl; 

    }

    cout << "Detecting ends ..." << endl; 

    //exercise 22
    const int grade = 40; 

    //conditional version
    string outcome = (grade > 90 ) ? "High pass" : ( grade > 75)?
            "pass" : ( grade >= 60 ) ? "low pass" : "fail"; 

    cout << "the grade " << grade << " is " << outcome << " with conditional version"<< endl; 

    // if version 

    const int grade1 = 91;
    string output = {}; 

    if (grade1 > 90){ 

        output = "high pass";

    }else if(grade1 > 75){

        output = "pass";

    }else if(grade1 >= 60){

        output = "low pass";

    }else{

        output = "fail";
        
    }

    cout << "the grade " << grade1 << " is " << output << " with if version"<< endl; 


}
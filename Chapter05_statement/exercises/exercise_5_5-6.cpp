#include <iostream>
#include <vector>
#include <string>

using std::endl; 
using std::cout; 
using std::cin;
using std::vector; 
using std::string; 

/*
* Exercise 5.5: 
* Using an if–else statement, write your own version of the
* program to generate the letter grade from a numeric grade.
* 
* Exercise 5.6: 
* Rewrite your grading program to use the conditional operator
* (§ 4.7, p. 151) in place of the if–else statement.
*/

int main(void){

    // inptu a number into score
    cout << "let's input a score here ..." << endl; 
    int score;
    cin >> score; 

    //grading scale
    vector<string> scale = {"failure", "E", "D", "C", "B", "A" }; 

    //let's write a if-statement version 
    //exercise 5
    cout << "executing ..." << endl; 
    int temp; 
    if( score <= 50 ){
        
        //failure status 
        cout << "your score is: " << scale[0] << " level ..." << endl;

    }else if( score <= 100 ){

        temp = score - 50; 
        // success status and now ensure which hierarcy they are
        cout << "your score is: " << scale[(temp-1)/10 + 1] << " level ..." << endl; 

    }else{

        cout << "score is unavaliable ... "<< endl;

    }

    //let's write conditional operator version 
    // exercise 6
    string status;
    status = ( score <= 50 ) ? scale[0] :
        ( score <= 100 ) ? scale[(score - 50 -1)/10 + 1] : "unavilable"; 
    cout << "your score is: " << status << endl;


}
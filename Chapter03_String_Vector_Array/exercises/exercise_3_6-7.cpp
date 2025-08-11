#include <iostream>
#include <string>

/*
* Exercise 3.6: Use a range for to change all the characters in a string to X.
* Exercise 3.7: What would happen if you define the loop control variable in
* the previous exercise as type char? Predict the results and then change your
* program to use a char to see if you were right.
*/

/*
* Answer to 3.7:  使用auto和char没有区别
*/

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void){

    string input; 

    //let's store into the variable input
    cin >> input; 
    
    //let's now handle it !!
    for ( auto &c : input ){

        c = 'X'; 

    }

    // let's print it !!
    cout << input << endl; 

    return 0; 

}
#include <iostream>
#include <string>

/*
* Exercise 3.8: What would happen if you define the loop control variable in
* the previous exercise as type char? Predict the results and then change your
* program to use a char to see if you were right.
*/

/* 
* Answer to 3.8: 我会更偏好 range-for + 引用：语义直接、少越界风险、可读性最好。
*/


using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void){

    string input;
    string input2;  

    //let's store into the variable input
    cin >> input >> input2;
    decltype( input.size() ) index = 0;
    
    //let's now handle it !!
    while( index < input.size()){

        input[index] = 'X';
        index++;

    }

    for( decltype( input2.size() ) i = 0; i < input2.size(); i++){

        input2[i] = 'X';

    }

    // let's print it !!
    cout << input << endl;
    cout << input2 << endl; 

    return 0; 

}
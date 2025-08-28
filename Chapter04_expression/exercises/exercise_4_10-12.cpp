#include <iostream>

using std::endl;
using std::cout;
using std::cin;

/*
* Exercise 4.10: Write the condition for a while loop that would read ints
* from the standard input and stop when the value read is equal to 42.
*/

/*
* Exercise 4.11: Write an expression that tests four values, a, b, c, and d,
* and ensures that a is greater than b, which is greater than c, which is
* greater than d.
*/

/*
* Exercise 4.12: Assuming i, j, and k are all ints, explain what i != j <
* k means.
*/

int main(void){

    int input;
    while ( (cin >> input ) && input != 42 ){

        cout << "you input the number: " << input << endl; 
    }

    //4.11 
    int a = 1, b = 3, c = 6, d = 10; 

    if( a > b && b > c && c > d){ 

        cout << "all four variables follow rule ...." << endl; 

    }else{

        cout << "four variables not follow rule ...." << endl; 

    }

    //12 
    // j compare with k first and then check if result is equal to the i 
    int i = 1, j = 10, k = 100; 
    cout << (i != j < k) << endl; 

}
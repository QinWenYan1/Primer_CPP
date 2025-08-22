#include <iostream>
#include <iterator>

/*
* Exercise 3.43: 
* Write three different versions of a program to print the
* elements of ia. One version should use a range for to manage the
* iteration, the other two should use an ordinary for loop in one case using
* subscripts and in the other using pointers. In all three programs write all the
* types directly. That is, do not use a type alias, auto, or decltype to
* simplify the code.
*/

/*
* Exercise 3.44: 
* Rewrite the programs from the previous exercises using a
* type alias for the type of the loop control variables.
*/

/*
* Exercise 3.45: Rewrite the programs again, this time using auto.
*/

using std::cout;
using std::cin;
using std::endl;
using std::begin;
using std::end; 

int main(void){

    int arr[4][5]  = {}; 

    //for range version 
    cout << "print for-range outcome ...." << endl;
    for (auto & e : arr){

        for (auto e : e){

            cout << e << " "; 

        }

        cout << endl; 

    }

    // for loop using subscript 
    cout << "print for-loop subscript outcome ...." << endl; 
    for (size_t i = 0; i < 4; i++ ){

        for (size_t j = 0; j < 5; j++){

            cout << arr[i][j] << " ";

        }
        
        cout << endl; 

    }

    //for loop using pointer
    using int_array = int (*)[5]; 
    cout << "print for-loop pointer with type alias outcome ...." << endl;
    for ( int_array pa = begin(arr); pa != end(arr); pa++){

        for( int* pi = begin(*pa); pi != end(*pa); pi++){

            cout << *pi << " ";

        }

        cout << endl; 

    }

    // using auto for for-loop
    cout << "print for-loop pointer with auto outcome ...." << endl; 
    for(auto outer_p = arr; outer_p != arr+4; outer_p++){

        for(auto inner_p = *outer_p; inner_p != (*outer_p)+5; inner_p++){

            cout << *inner_p << " "; 

        } 
        cout << endl; 
    }

}
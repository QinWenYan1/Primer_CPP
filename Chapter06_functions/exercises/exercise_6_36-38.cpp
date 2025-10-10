#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
* Exercise 6.36: Write the declaration for a function that returns a reference
* to an array of ten strings, without using either a trailing return,
* decltype, or a type alias.
*/

/*
* Exercise 6.37: Write three additional declarations for the function in the
* previous exercise. One should use a type alias, one should use a trailing
* return, and the third should use decltype. Which form do you prefer and
* why?
*/

string (&refer_to_str())[10];

//type alias form 
typedef string (&seq_str)[10] ; 
using sequence_str = string (&)[10]; 
seq_str ref_to_str(); 
sequence_str refence_str(); 

//trailing return 
auto trailing_ref_str() -> string (&)[10]; 

//decltype return 
seq_str var; 
decltype(var) dec_refer_str(){}; 

/*
* Answer: 更喜欢trailing return, 简洁明了，安全预防error-prone
*/

/*
* Exercise 6.38: Revise the arrPtr function on to return a reference to the
* array.
*
* int odd[] = {1,3,5,7,9};
* int even[] = {0,2,4,6,8};
* // returns a pointer to an array of five int elements
* decltype(odd) *arrPtr(int i)
* {
*   return (i % 2) ? &odd : &even; // returns a pointer to the array
* }
*/

int odds [] = {1, 3, 5, 7, 9};
int evens [] = {0, 2, 4, 6, 8};
decltype(odds) & arrPtr(int i){

    return (i % 2 )? odds : evens; 

}




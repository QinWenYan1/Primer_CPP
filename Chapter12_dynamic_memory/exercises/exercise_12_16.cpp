#include <iostream>
#include <memory>

using namespace std;

/*
* Exercise 12.16: 
* Compilers don’t always give easy-to-understand error
* messages if we attempt to copy or assign a unique_ptr. Write a program
* that contains these errors to see how your compiler diagnoses them.
*/

int main(){

    unique_ptr<int> uiptr(new int(1145)); 
    unique_ptr<int> uniptr; 
    /*
    * function "std::__1::unique_ptr<_Tp, _Dp>::operator=(const std::__1::unique_ptr<int, std::__1::default_delete<int>> &) [with _Tp=int, _Dp=std::__1::default_delete<int>]" 
    * (declared implicitly) cannot be referenced -- it is a deleted functionC/C++(1776)
    */
    //uniptr = uiptr; 
    //unique_ptr<int> test(uiptr); 

}
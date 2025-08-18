#include <iostream>
#include <iterator>
#include <vector>

/*
* Exercise 3.36: 
* Write a program to compare two arrays for equality. Write a
* similar program to compare two vectors.
*/
using std::end; 
using std::begin;
using std::cout;
using std::cin;
using std::endl;
using std::vector; 

int main(void){

    //create examples for comparison 
    int arr[10] = {};
    int arr2[10] = {1,1,1};

    //now let's start comparing 
    //comparing size first
    int *pbegn = begin(arr);
    int *pend = end(arr); 
    int *pbegn2 = begin(arr2);
    int *pend2 = end(arr2); 
    
    auto dist = pbegn - pend;
    auto dist2 = pbegn2 - pend2;

    //if equal, let's compare two arrays
    if( dist == dist2 ){

        bool flag = 0; 
        for(; pbegn != pend; pbegn++){

            if( *pbegn != *pbegn2 ){ flag = 1; }

        }

        if(flag){ cout << "two arrays are not equal in elements' values..." << endl; }

    }else{ cout << "two arrays are not equal in size..." << endl; }


    //now, let's compare two vectors 
    vector<int> v(10);
    vector<int> v2(10, 1);

    if( v != v2 ){ cout << "two vectors are not equal...." << endl; }


    

}
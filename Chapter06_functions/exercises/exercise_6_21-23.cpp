#include <iostream>
#include <iterator>

using std::cout;
using std::cin;
using std::endl; 
using std::begin;
using std::end; 

/*
* Exercise 6.21: 
* Write a function that takes an int and a pointer to an int
* and returns the larger of the int value or the value to which the pointer
* points. What type should you use for the pointer?
*/

/*
* Exercise 6.22: 
* Write a function to swap two int pointers.
*/

/*
* Exercise 6.23: 
* Write your own versions of each of the print functions
* presented in this section. Call each of these functions to print i and j
* defined as follows:
* int i = 0, j[2] = {0, 1};
*/

/* 
* 描述：打印数组输入值
* 返回：void
* 输入: const int *, const int *
*/
void print(const int * begin, const int * end){

    cout << "Printed value is: "; 

    for (const int* ptr = begin; ptr != end; ++ ptr){

        cout << *begin; 

    }

    cout << endl; 

}

/* 
* 描述：打印输入值
* 返回：void
* 输入: const int v
*/

void print(const int v){

    cout << "Printed value is: " << v << endl; 

}


/* 
* 描述：根据输入，用于返回更大的int值
* 返回：int 
* 输入: const int&, const int* 
*/
int larger_value(const int& v1, const int* v2){

    const int outcome = (v1 > *v2)? v1 : *v2; 
    return outcome; 

};

/*
* 描述：交换两个it pointer
* 返回: void
* 输入：const int*, const int* 
*/
void swap(const int* &v1, const int* &v2){

    const int *temp = v1; 
    v1 = v2; 
    v2 = temp; 

};

int main(void){

    cout << "Begin comparing ..." << endl; 
    int v1 = 114, v2 = 514; 

    cout << "Original data v1: "
         << v1 << "\n"
         << "Original data v2: "
         << v2 << endl; 
    
    cout << "The outcome of comparing is: " << larger_value(v1, &v2) << endl; 

//--------------------

    cout << "Let's swap two pointers" << endl;  
    const int *ptr1 = &v1, *ptr2 = &v2; 

    cout << "The original pointer: " << ptr1 << "\n"
         << "The original pointer: " << ptr2 << endl; 
    
    cout << "Swapping ..." << endl; 
    swap(ptr1, ptr2);

    cout << "The pointer: " << ptr1 << "\n"
         << "The pointer: " << ptr2 << endl;

//--------------------

    cout << "Let's print values ..." << endl; 
    int v = 15; 
    int arr [5] = {1,2,3,4,5}; 
    print(v);
    print(begin(arr), end(arr)); 

}
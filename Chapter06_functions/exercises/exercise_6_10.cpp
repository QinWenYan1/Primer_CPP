#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*
* Exercise 6.10: 
* Using pointers, write a function to swap the values of two
* ints. Test the function by calling it and 
* printing the swapped values.
*/

//用于交换实参对象的值，并且打印下来
// return type: void
// parameter type: int*, int*
void swap(int *first, int *second){

    cout << "The value of two objects are: "
         << *first << " , " << *second << endl; 
    cout <<"Swapping ..." << endl; 

    int temp = *first; 
    *first = *second; 
    *second = temp; 

    cout << "The value of two objects are: "
         << *first << " , " << *second << endl; 

}

int main(void){
    
    int row = 14, col = 200; 
    swap(&row, &col); 
    cout << "Testing swapping outcome ... \n"
         << "Row is: " << row << "\n"
         << "Col is: " << col 
         << endl; 

}
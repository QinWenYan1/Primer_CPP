#include <iostream>
#include <initializer_list>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::initializer_list;
using std::vector;


/*
* Exercise 6.27: 
* Write a function that takes an initializer_list<int>
* and produces the sum of the elements in the list.
*/

int sum(initializer_list<int> nums){

    auto head = nums.begin(), tail = nums.end();
    int sum = 0; 

    while( head != tail ){

        sum += *head; 
        ++ head; 

    }

    return sum;

}

int main(void){

    cout << "Lets print some outcomes to test ..." << endl; 
    cout << "1, 2, 3, 114, 514 ..." << endl;
    cout << "The outcome is: " << sum({1,2,3,114,514}) << endl;

    cout << "177, 3685, 8105" << endl;
    cout << "The outcome is: " << sum({177, 3685, 8105}) << endl;

}

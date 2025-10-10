#include <iostream>
#include <vector>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl; 
using std::vector; 

/*
* Exercise 6.33: Write a recursive function to print the contents of a vector.
*/

void print_rec(vector<int>::iterator head, vector<int>::iterator tail){
    
    if(head != tail){

        cout << (*head) << " "; 
        print_rec(head+1, tail); 

    } 
    
}

int main(void){

    vector<int> v = {1, 31, 134, 1145, 14, 1919}; 
    print_rec(v.begin(), v.end()); 
    return EXIT_SUCCESS;

}


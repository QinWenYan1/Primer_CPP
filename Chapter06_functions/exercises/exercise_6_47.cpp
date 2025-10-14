#include <vector>
#include <iostream>
#include <cstdlib>

using std::vector;
using std::cout; 
using std::cerr;
using std::endl; 

/*
* Exercise 6.47: 
* Revise the program you wrote in the exercises in § 6.3.2 (p.
* 228) that used recursion to print the contents of a vector to conditionally
* print information about its execution. For example, you might print the size of
* the vector on each call. Compile and run the program with debugging
* turned on and again with it turned off.
*/

// original version 
void print_rec(vector<int>::iterator head, vector<int>::iterator tail){
    #ifndef NDEBUG 
    if (tail < head ){

        cerr << "Error detecting ..." << endl; 
        cerr << "Error information:" << endl; 
        cerr << "File: " << __FILE__ << " "
             << "Function: " << __func__ << " "
             << "Error on line " << __LINE__ << "\n"
             << "Compile on: " << __DATE__ << " at " << __TIME__ << "\n" 
             << "Error: Overflow"; 
        return; 

    }else{

        cout << "Execution success" << endl;  
        cerr << "File: " << __FILE__ << " "
             << "Function: " << __func__ << " "
             << "Compile on: " << __DATE__ << " at " << __TIME__ << endl;
        cout << "Vector size: " << (tail - head) << endl; 

    }
    #endif
    
    if(head != tail){

        cout << (*head) << " "; 
        print_rec(head+1, tail); 

    } 
    
}


int main(){

    vector<int> v1 = {1145, 14, 1919, 2025, 110, 120}; 
    print_rec(v1.begin(), v1.end());
    return EXIT_SUCCESS; 

}

 
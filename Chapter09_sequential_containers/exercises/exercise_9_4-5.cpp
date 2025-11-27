#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using std::vector; 
using std::cout; 
using std::ofstream; 
using std::endl; 
using std::stoi; 

/*
* Exercise 9.4: 
* Write a function that takes a pair of iterators to a
* vector<int> and an int value. Look for that value in the range and return
* a bool indicating whether it was found.
* 
* Exercise 9.5: 
* Rewrite the previous program to return an iterator to the
* requested element. Note that the program must handle the case where the
* element is not found.
*/

static vector<int> v = {114, 514, 120, 110, 510, 1, 43, 21, 110};

int main(int argc, char* argv[]){
 
    int target = stoi(argv[1]); 
    ofstream output("log.txt", ofstream::app); 

    for(auto beginner = v.begin(); beginner != v.end(); ++beginner){

        if((*beginner) == target ){ 
            
            cout << "Successfully find target " << target << endl;
            output << "Successfully find target " << target << endl; 
            return 0; 
        
        }

    }

    cout << "Unsuccessfully find target " << target << endl;
    output << "Unsuccessfully find target " << target << endl; 
    
}
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl; 


/*
* Exercise 3.20: 
* Read a set of integers into a vector. Print the sum of each
* pair of adjacent elements. Change your program so that it prints the sum of
* the first and last elements, followed by the sum of the second and second-to-
* last, and so on.
*/

int main(void){

    // create an integer container
    vector<int> set;
    decltype(set.size()) index = 0;
    int temp; 
    
    //take numbers into container first
    while( cin >> temp ){ set.push_back(temp); };

    //now begin to calculate: if only one or none number left,, stop calculating
    for(; index < ( set.size() ) / 2; index++){
        
        int sum = set[index] + set[ set.size() - index - 1 ]; 
        cout << "The sum of " << set[index] << " and " << set[ set.size() - index - 1]
        << " is " << sum << endl;

    }

    cout << "end calculation" << endl; 

}
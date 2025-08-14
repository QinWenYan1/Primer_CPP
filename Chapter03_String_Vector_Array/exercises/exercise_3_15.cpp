#include <iostream>
#include <vector>


/*
* Exercise 3.15: 
* Repeat the previous program but read strings this time.
*/

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

int main(void){

    //create integer container 
    vector<string> v; 
    string temp; 


    //input prompt 
    cout << "please input series of strings below:" <<endl; 
    while( cin >> temp ){

        v.push_back(temp);

    }

    //now list all elements
    cout << "the outcome: " << endl; 
    for(auto element : v){
        cout << element << endl; 
    }

}
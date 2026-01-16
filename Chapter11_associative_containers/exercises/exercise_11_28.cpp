#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std; 

/*
* Exercise 11.28: 
* Define and initialize a variable to hold the result of calling
* find on a map from string to vector of int.
*/

int main(){

    map<string, vector<int>> m = 
        { {"Qinwen", {1145,14}},{"Yan", {205, 6}} }; 
    
    map<string, vector<int>>::iterator target= m.find("Qinwen");
    cout << target->second[0] << endl;



}
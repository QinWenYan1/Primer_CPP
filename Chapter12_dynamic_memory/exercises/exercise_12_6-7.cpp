#include <iostream>
#include <vector>
#include <memory>
#include <new>

using namespace std; 

/*
* Exercise 12.6: 
* Write a function that returns a dynamically allocated vector
* of ints. Pass that vector to another function that reads the standard input
* to give values to the elements. Pass the vector to another function to print
* the values that were read. Remember to delete the vector at the
* appropriate time.
*/

/*
* Exercise 12.7: 
* Redo the previous exercise, this time using shared_ptr.
*/

vector<int> *vectorFactory(){

    vector<int> *vp = new(nothrow) vector<int>; 
    return vp; 

}

 shared_ptr<vector<int>> sharedVectorFactory(){

    auto vp = make_shared<vector<int>>(); 
    return vp; 

}

shared_ptr<vector<int>> readDataForShared(shared_ptr<vector<int>> vp){
    
    int temp = 0; 
    while(cin >> temp){ vp->push_back(temp); }
    return vp; 

}

vector<int> *readData(vector<int>* vp){
    
    int temp = 0; 
    while(cin >> temp){ vp->push_back(temp); }
    return vp; 

}

void destroy(vector<int>* vp){

    delete vp; 
    vp = nullptr; 

}

int main(){

    auto p = sharedVectorFactory(); 
    readDataForShared(p);
    cout << "The outcome is: " << endl; 
    for (const auto &e: *p ) { cout << e << " "; }
    cout << endl; 
    cout << "task Compelete ..." << endl; 

}


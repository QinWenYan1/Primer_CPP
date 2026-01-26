#include <fstream>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <iterator>
#include "StrBlobPtr.h"

using namespace std;

/*
* Exercise 12.20: 
* Write a program that reads an input file a line at a time
* into a StrBlob and uses a StrBlobPtr to print each element in that
* StrBlob.
*/

int main(){

    ifstream input("input.txt"); 
    istream_iterator<string> beginner(input), eof; 

    StrBlob sb; 
    while (beginner != eof) sb.push_back(*beginner++);
    
    StrBlobPtr sbManipulator(sb); 

    try{

        string obj; 
        while(!sb.empty()){
            cout << sbManipulator.deref() << endl; 
            sbManipulator.incr(); 
        }

    }catch(runtime_error re){
        cout << re.what() << endl; 
    }catch(out_of_range oe){
        cout << oe.what() << endl;
    }

}

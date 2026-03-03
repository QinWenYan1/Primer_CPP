/*
* Exercise 14.34: 
* Define a function-object class to perform an if-then-else
* operation: The call operator for this class should take three parameters. It
* should test its first parameter and if that test succeeds, it should return its
* second parameter; otherwise, it should return its third parameter.
* 
* Exercise 14.37: 
* Write a class that tests whether two values are equal. Use
* that object and the library algorithms to write a program to replace all
* instances of a given value in a sequence.
* 
* 略过，就不写了
*/

/*
* Exercise 14.35: 
* Write a class like PrintString that reads a line of input
* from an istream and returns a string representing what was read. If the
* read fails, return the empty string.
*/

/*
* Exercise 14.36: 
* Use the class from the previous exercise to read the
* standard input, storing each line as an element in a vector.
*/

#include <iostream>
#include <string>
#include <vector>

class PrintString{

public:
    PrintString(std::istream &is = std::cin): input(is){}

    std::string operator()(){
        std::string temp; 
        getline(input, temp); 
        return temp; 
    }

private:
    std::istream &input; 

}; 

using namespace std; 

int main(){

    PrintString printer(std::cin); 
    string str; 
    vector<string> vecStr; 
    while (!(str = printer()).empty()){
        vecStr.push_back(str); 
    }

    for(const auto e: vecStr){
        cout << e << endl; 
    }
    
}
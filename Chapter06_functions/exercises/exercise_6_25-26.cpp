#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl; 
using std::string; 

/*
* Exercise 6.25: 
* Write a main function that takes two arguments.
* Concatenate the supplied arguments and print the resulting string.
* Exercise 6.26: 
* Write a program that accepts the options presented in this
* section. Print the values of the arguments passed to main.
*/

int main(int argc, char* argv[]){

    if (argc == 1) return 1; 

    string v1 = argv[1], v2 = argv[2]; 

    v1 += v2; 

    cout << "The outcome concatenate is: "  << v1 << endl; 

    cout << "Print all options ..." << endl; 
    for(size_t i = 1; i != argc; ++ i){

        cout << argv[i] << " ";

    }

    cout << endl; 

    return 0; 

}

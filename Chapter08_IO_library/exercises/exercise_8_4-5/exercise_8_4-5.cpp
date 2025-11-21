#include <fstream>
#include <string>
#include <vector>
#include <iostream>

/*
* Exercise 8.4: 
* Write a function to open a file for input and read its contents
* into a vector of strings, storing each line as a separate element in the
* vector.
* 
* Exercise 8.5: 
* Rewrite the previous program to store each word in a
* separate element.
*/

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;

int main(){

    //read by words 
    cout << "Let's read by words first:" << "\n"; 
    string temp; 
    vector<string> storage;

    ifstream input("test.txt");

    while(input >> temp){ 
        
        storage.push_back(temp); 
        storage.push_back("\n"); //插入间隔元素
    
    }

    //now, we run a console output to see if it works 
    for (auto e: storage){ cout << e; }

    //重启一下文件流
    input.close();
    input.open("test.txt");

    //read by seperate lines  
    cout << "Let's read by lines first:" << "\n";
    string line;
    vector<string> lines; 

    while(getline(input, line)){ 
        lines.push_back(line); 
        lines.push_back("\n");
    }

    for (auto e: lines){ cout << e; }

}





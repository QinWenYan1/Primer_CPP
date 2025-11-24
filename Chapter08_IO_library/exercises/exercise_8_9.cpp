#include <iostream>
#include <sstream>

using std::istream; 
using std::istringstream; 
using std::string; 
using std::cout;
using std::cin; 
using std::endl; 

/*
* Exercise 8.9: 
* Use the function you wrote for the first exercise in § 8.1.2 (p.
* 314) to print the contents of an istringstream object.
*/

istream& readUntilEnd(istream& input){

    string word; 
    while(input >> word){ cout << word; cout << " "; }
    cout << endl; 

    //此时cin的状态是failling的我们需要将其clear再返回
    input.clear(); 

    return input; 

}

int main(){

    //将标准输入的output放入到istringstream对象中
    //然后使用我们写的function来处理istringstream对象

    string line; 
    while(getline(cin, line)){

        istringstream entry(line); 
        readUntilEnd(entry); 

    }


}
#include <iostream>

using std::istream; 
using std::cout;
using std::cin; 
using std::endl; 

/*
* Exercise 8.1: 
* Write a function that takes and returns an istream&. The
* function should read the stream until it hits end-of-file. The function should
* print what it reads to the standard output. Reset the stream so that it is valid
* before returning the stream.
*
* Exercise 8.2: 
* Test your function by calling it, passing cin as an argument.
*/

istream& readUntilEnd(istream& input){

    char word; 
    while(cin >> word){

        cout << word; 

    }
    cout << endl; 

    //此时cin的状态是failling的我们需要将其clear再返回
    cin.clear(); 

    return cin; 

}

int main(){

    //我们运行一下，测试一下
    //检查cin的状态是否符合已经恢复

    readUntilEnd(cin); 
    cout << "cin 状态为： " << cin.good() << endl; 

}
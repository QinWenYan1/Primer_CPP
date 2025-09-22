#include <iostream>

using std::cout;
using std::cin;
using std::endl; 

/*
* Exercise 6.7: 
* Write a function that returns 0 when it is first called and then
* generates numbers in sequence each time it is called again.
*/

//每次调用本函数我们就依次递增打印整数
// return type: int 
// paramter type: none
int call_count(){

    static size_t count; 
    return count ++; 

}

int main(void){

    //我们检验一下，我们写的函数是否正确
    cout << "Please print outcome ..." << endl; 
    for ( int i = 0; i < 10; ++i ){

        cout << call_count() << endl; 

    }
    

}
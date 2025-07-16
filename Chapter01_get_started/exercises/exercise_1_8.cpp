#include <iostream>

/*
* Exercise 1.8: 
* Indicate which, if any, of the following output statements are
* legal:
*/

int main(void){

    std::cout << "/*" << std::endl;
    std::cout << "*/" << std::endl;
    //std::cout << /*"/*"*/ << std::endl;  注释掩盖了字符串引号，语法不完整 
    std::cout << /* "*/" /* "/*" */ << std::endl;
    
}
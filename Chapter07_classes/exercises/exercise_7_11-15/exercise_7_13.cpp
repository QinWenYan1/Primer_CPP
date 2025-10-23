#include <iostream>
#include <cstdlib>
#include "Sales_data.h"

using std::cout; 
using std::cin; 
using std:: endl; 
using std::string; 
using std::cerr; 

/*
* Exercise 7.13: 
* Rewrite the program from page 255 to use the istream
* constructor.
*/

int main(){

    Sales_data total = Sales_data(cin); 

    Sales_data trans; //用于存下一个书的数据的变量

    while( read( cin, trans ) ){

        if( trans.isbn() == total.isbn() ) {

            total.combine(trans);  

        } 
        else {

            // 进入一本新的书了， 我们需要打印上一本书的信息
            print(cout, total) << endl;
            total = trans;  

        }
    }

    //已经读取完了， 我们需要将手上的信息打印出去
    print(cout, total) << endl; 

    



}
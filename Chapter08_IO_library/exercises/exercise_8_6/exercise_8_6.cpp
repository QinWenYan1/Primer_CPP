#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Sales_data.h"

using std::cout; 
using std:: endl; 
using std::string; 
using std::cerr; 
using std::ifstream; 
 

/*
* Exercise 8.6: 
* Rewrite the bookstore program from § 7.1.1 (p. 256) to read
* its transactions from a file. Pass the name of the file as an argument to main
* (§ 6.2.5, p. 218).
*/

int main(){

    ifstream input("transaction_log.txt");

    Sales_data total = Sales_data(input); 

    Sales_data trans; //用于存下一个书的数据的变量

    while( read( input, trans ) ){

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
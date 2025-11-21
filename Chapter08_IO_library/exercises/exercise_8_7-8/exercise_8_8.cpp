#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Sales_data.h"

using std:: endl; 
using std::string; 
using std::cerr; 
using std::ifstream; 
using std::ofstream; 
 

/*
* Exercise 8.8: 
* Revise the program from the previous exercise to append its
* output to its given file. Run the program on the same output file at least
* twice to ensure that the data are preserved.
*/ 

int main(int argc, char* argv[]){

    string target_name = argv[1]; //目标文件的名字

    //建立文件流
    ifstream input("transaction_log.txt");
    ofstream out(target_name, ofstream::app); 

    Sales_data total = Sales_data(input); 

    Sales_data trans; //用于存下一个书的数据的变量

    while( read( input, trans ) ){

        if( trans.isbn() == total.isbn() ) {

            total.combine(trans);  

        } 
        else {

            // 进入一本新的书了， 我们需要打印上一本书的信息
            print(out, total) << endl;
            total = trans;  

        }
    }

    //已经读取完了， 我们需要将手上的信息打印出去
    print(out, total) << endl; 

}
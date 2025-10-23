#include <iostream>
#include <cstdlib>
#include "Sales_data.h"

using std::cout; 
using std::cin; 
using std:: endl; 
using std::string; 
using std::cerr; 

/*
* Exercise 7.7: 
* Rewrite the transaction-processing program you wrote for the
* exercises in § 7.1.2 (p. 260) to use these new functions.
*/

int main(){

    Sales_data total; 

    if( read( cin, total ) ){

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

    }else{

        cerr << "No any data input ! ..." << endl; //通知使用者，没有任何输入

    }



}
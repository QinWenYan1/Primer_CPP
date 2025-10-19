#include <iostream>
#include <cstdlib>
#include "Sales_data.h"

using std::cout; 
using std::cin; 
using std:: endl; 
using std::string; 
using std::cerr; 

/*
* Exercise 7.3: 
* Revise your transaction-processing program from § 7.1.1 (p.
* 256) to use these members.
*/

int main(){

    Sales_data total; 

    if( (cin >> total.bookNo >> total.price >> total.units_sold) ){

        Sales_data trans; //用于存下一个书的数据的变量

        while( (cin >> trans.bookNo >> trans.price >> trans.units_sold) ){

            if( trans.isbn() == total.isbn() ) {

                total.combine(trans);  

            } 
            else {

                // 进入一本新的书了， 我们需要打印上一本书的信息
                cout << "Book isbn: " << total.isbn() << endl; 
                cout << "Book price: " << total.price << endl; 
                cout << "Book total sold number: " << total.units_sold << endl; 
                total = trans;  

            }
        }

        //已经读取完了， 我们需要将手上的信息打印出去
        cout << "Book isbn: " << total.isbn() << endl; 
        cout << "Book price: " << total.price << endl; 
        cout << "Book total sold number: " << total.units_sold << endl;

    }else{

        cerr << "No any data input ! ..." << endl; //通知使用者，没有任何输入

    }



}
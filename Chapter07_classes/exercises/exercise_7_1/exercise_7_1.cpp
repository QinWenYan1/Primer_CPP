#include <iostream>
#include <cstdlib>
#include "Sales_data.h"

using std::cout; 
using std::cin; 
using std:: endl; 
using std::string; 
using std::cerr; 

/*
* Exercise 7.1: 
* Write a version of the transaction-processing program from §
* 1.6 (p. 24) using the Sales_data class you defined for the exercises in §
* 2.6.1 (p. 72).
*/

int main(){

    Sales_data total; 

    if( (cin >> total.bookNo >> total.price >> total.units_sold) ){

        Sales_data trans; //用于存下一个书的数据的变量

        while( (cin >> trans.bookNo >> trans.price >> trans.units_sold) ){

            if( trans.bookNo == total.bookNo ) {

                double total_price = total.price * total.units_sold 
                    + trans.units_sold * trans.price; 

                total.units_sold += trans.units_sold; 

                total.price = total_price / total.units_sold; 

            } 
            else {

                // 进入一本新的书了， 我们需要打印上一本书的信息
                cout << "Book isbn: " << total.bookNo << endl; 
                cout << "Book price: " << total.price << endl; 
                cout << "Book total sold number: " << total.units_sold << endl; 
                total = trans;  

            }
        }

        //已经读取完了， 我们需要将手上的信息打印出去
        cout << "Book isbn: " << total.bookNo << endl; 
        cout << "Book price: " << total.price << endl; 
        cout << "Book total sold number: " << total.units_sold << endl;

    }else{

        cerr << "No any data input ! ..." << endl; //通知使用者，没有任何输入

    }



}
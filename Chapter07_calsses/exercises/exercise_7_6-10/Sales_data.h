#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>
 

/*
* Exercise 7.6: 
* Define your own versions of the add, read, and print
* functions.
*/

/*
* Exercise 7.8: 
* Why does read define its Sales_data parameter as a plain
* reference and print define its parameter as a reference to const?
*/

/*
* Answer: 
* 在read function里面， 我们需要将输入流的数据写入到目标实例
* 所以需要改动到实例的数据， 不能使用const
* 然而在print function里面， 我们不需要改动实例， 只需要将其数据打印
* 因此我们应该添加const去保护我们的数据安全
*/

/*
* 你的代码思路完全正确，主要是一些实现细节需要优化。特别是：

* 头文件中避免using声明

* 函数参数尽量使用const引用


*/



struct Sales_data{
 

    //member data 
    unsigned units_sold = 0;
    double price = 0.0;   
    std::string bookNo; 

    //member function declaration 

    //返回本书的isbn信息
    const std::string& isbn() const { return bookNo; }

    //将右边类加入到左边类
    Sales_data& combine(Sales_data obj1){

        units_sold += obj1.units_sold; 
        double total_price = units_sold * price + 
                             (obj1.units_sold) * (obj1.price);
        price = avg_price(total_price, units_sold);
        return *this; 

    }

    //计算平均price在combine之后
    double avg_price(double total_price, unsigned total_num){ 

        return total_price/total_num; 

    } 



};

//nonmember funciton, but same interface 


//读取数据进入到实例中，返回输入流，支持链式操作
std::istream &read( std::istream &in, Sales_data &item ){

    in >> item.bookNo >> item.price >> item.units_sold;  
    return in; 

};

//将实例的数据打印出来， 返回输出流，支持链式操作
std::ostream &print(std::ostream &out, const Sales_data &item){

    out << "ISBN number: " << item.bookNo << " "
        << "Average price: " << item.price << " "
        << "Sold number: " << item.units_sold << " ";

    return out; 

}


//读取俩个item, 相加，合成一个item 
Sales_data add(const Sales_data &lhs, const Sales_data &rhs){

    Sales_data new_item = lhs; 
    new_item.combine(rhs); 
    return new_item; 

}



#endif
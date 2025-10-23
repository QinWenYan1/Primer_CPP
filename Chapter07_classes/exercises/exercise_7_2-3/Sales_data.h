#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

/*
* Exercise 7.2: 
* Add the combine and isbn members to the Sales_data
* class you wrote for the exercises in § 2.6.2 (p. 76)
*/

struct Sales_data{

    //member data 
    unsigned units_sold = 0;
    double price = 0.0;   
    std::string bookNo; 

    //member function declaration 

    //返回本书的isbn信息
    const std::string& isbn() const; 

    //将右边类加入到左边类
    Sales_data& combine(Sales_data); 

    //计算平均price在combine之后
    double avg_price(double, unsigned); 



};

/*member function definition*/
const std::string& Sales_data::isbn() const { return bookNo; }

Sales_data& Sales_data::combine(Sales_data obj1){

    units_sold += obj1.units_sold; 
    double total_price = units_sold * price + (obj1.units_sold) * (obj1.price);

    price = avg_price(total_price, units_sold);

    return *this; 

}

double Sales_data::avg_price(double total_price, unsigned total_num){ 

    return total_price/total_num; 

}

#endif
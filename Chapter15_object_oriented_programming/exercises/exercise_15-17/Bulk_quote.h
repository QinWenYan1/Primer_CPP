#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "Disc_quote.h"
#include <string>
#include <iostream>

/*
* Exercise 15.15: 
* Define your own versions of Disc_quote and Bulk_quote.
* 
* Exercise 15.16: 
* Rewrite the class representing a limited discount strategy,
* which you wrote for the exercises in § 15.2.2 (p. 601), to inherit from
* Disc_quote.
* 
* Exercise 15.17: 
* Try to define an object of type Disc_quote and see what
* errors you get from the compiler.
*/

class Bulk_quote : public Disc_quote{

public:
    Bulk_quote() = default; //默认构造函数
    Bulk_quote(const std::string &book, const double &sales_price, const double &discount, const std::size_t &quan): 
        Disc_quote(book, sales_price, discount, quan)   
    {} //构造函数
    ~Bulk_quote() override = default; //析构函数

    const size_t getDiscountQuan() const { return quantity; }

    //虚函数定义实现
    double net_price(std::size_t n ) const override { return quantity*price*discount + n*price; } 
    std::ostream & debug(std::ostream &os) const override {

        os << "NAME: " << isbn() << " "
            << "Price: " << price << " "
            << "Sold quantity: " << quantity << " "
            << "Discount: " << discount; 
        return os; 

    } 

    
}; 

inline double print_total(std::ostream &os, const Bulk_quote &item, const std::size_t &count){

    double ret = item.net_price(count);
    os << "ISBN: " << item.isbn() // calls Quote::isbn
    << " # sold: " << (count+item.getDiscountQuan()) << " total due: " << ret << std::endl;
    return ret;

}

#endif 

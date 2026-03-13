#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H
#include "Quote.h"
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

class Disc_quote : public Quote{

public:
    Disc_quote() = default; //默认构造函数
    Disc_quote(const std::string &book, const double &sales_price, const double &discount, const std::size_t &quan): 
        Quote(book, sales_price),
        discount(discount),
        quantity(quan)
    {} //构造函数
    ~Disc_quote() override = default; //析构函数


protected:
    double discount = 0.0;  //discount力度
    std::size_t quantity = 0; //discount的数量 
    
}; 

#endif 
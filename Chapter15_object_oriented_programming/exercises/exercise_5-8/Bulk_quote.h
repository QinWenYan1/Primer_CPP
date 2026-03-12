#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "Quote.h"
#include <string>
#include <iostream>

/*
* Exercise 15.5: 
* Define your own version of the Bulk_quote class.
*
* Exercise 15.6: 
* Test your print_total function from the exercises in §
* 15.2.1 (p. 595) by passing both Quote and Bulk_quote objects o that
* function.
*/

class Bulk_quote : public Quote{

public:
    Bulk_quote() = default; //默认构造函数
    Bulk_quote(const std::string &book, const double &sales_price, const double &discount): 
        Quote(book, sales_price),
        discount(discount)
    {} 
    double net_price(std::size_t n ) const override { return n*price*discount; }
    ~Bulk_quote() override = default; 

private:
    double discount; 
    

}; 


#endif 
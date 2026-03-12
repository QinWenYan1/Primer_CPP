#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "Quote.h"
#include <string>
#include <iostream>

/*
* Exercise 15.11: 
* Add a virtual debug function to your Quote class hierarchy
* that displays the data members of the respective classes.
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
    virtual std::ostream & debug(std::ostream &os) const override {
        Quote::debug(os) << " discount: "; 
        std::cout << discount << std::endl; 
        return os; 

    }

private:
    double discount; 
    
}; 

#endif 
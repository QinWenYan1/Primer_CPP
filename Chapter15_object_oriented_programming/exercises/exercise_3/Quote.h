#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>

/*
* Exercise 15.3: 
* Define your own versions of the Quote class and the
* print_total function.
*/

class Quote {

public:
    Quote() = default; //默认构造函数
    Quote(const std::string &book, const double &sales_price):
        bookNo(book), price(sales_price) {} 
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n ) const { return n*price; }
    virtual ~Quote() = default; 
    
private:
    const std::string bookNo;

protected:
    double price; 

}; 

inline double &print_total(std::ostream &os, const Quote &item, const std::size_t &count){

    double ret = item.net_price(count);
    os << "ISBN: " << item.isbn() // calls Quote::isbn
    << " # sold: " << count << " total due: " << ret << std::endl;
    return ret;

}
 


#endif 
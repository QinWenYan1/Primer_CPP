#ifndef QUOTE_H
#define QUOTE_H

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

class Quote {

public:
    Quote() = default; //默认构造函数
    Quote(const std::string &book, const double &sales_price):
        bookNo(book), price(sales_price) {} 
    std::string isbn() const { return bookNo; }
    virtual ~Quote() = default; 

    virtual double net_price(std::size_t n) const = 0; 
    virtual std::ostream &debug(std::ostream &os) const = 0; 
    
private:
    const std::string bookNo;

protected:
    double price; 

}; 


#endif 
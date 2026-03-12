#ifndef QUOTE_H
#define QUOTE_H

#include <string>

class Quote {

public:
    Quote() = default; //默认构造函数
    Quote(const std::string &book, const double &sales_price):
        bookNo(book), price(sales_price) {} 
    std::string isbn(){ return bookNo; }

    virtual double net_price(std::size_t n ) const { return n*price; }
    
    virtual ~Quote() = default; 
    
    
private:
    const std::string bookNo;

protected:
    double price; 

}; 

#endif 